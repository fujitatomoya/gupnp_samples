#include <libgupnp/gupnp.h>
#include <stdlib.h>
#include <gmodule.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

// Global Variables.
static gboolean status;
static gboolean quiet;

// Optional Argument.
static GOptionEntry entries[] =
{
  { "quiet", 'q', 0, G_OPTION_ARG_NONE, &quiet, "Turn off output", NULL },
  { NULL }
};

// Callback Declaration.
G_BEGIN_DECLS
G_MODULE_EXPORT void set_target_cb(GUPnPService *service,
                                   GUPnPServiceAction *action,
                                    gpointer user_data);
G_MODULE_EXPORT void get_target_cb(GUPnPService *service,
                                   GUPnPServiceAction *action,
                                   gpointer user_data);
G_MODULE_EXPORT void get_status_cb(GUPnPService *service,
                                   GUPnPServiceAction *action,
                                   gpointer user_data);
G_MODULE_EXPORT void query_target_cb(GUPnPService *service, char *variable,
                                     GValue *value, gpointer user_data);
G_MODULE_EXPORT void query_status_cb(GUPnPService *service, char *variable,
                                     GValue *value, gpointer user_data);
G_END_DECLS

/*
 * Action implementations
 */

/* SetTarget */
G_MODULE_EXPORT void
set_target_cb(
  GUPnPService *service,
  GUPnPServiceAction *action,
  G_GNUC_UNUSED gpointer user_data)
{
  gboolean target;

  /* Get the new target value */
  gupnp_service_action_get(
    action,
    "newTargetValue", G_TYPE_BOOLEAN, &target,
    NULL);

  /*
   * If the new target doesn't match the current status,
   * change the status and emit a notification that the status has changed.
   */
  if (target != status) {
    status = target;
    gupnp_service_notify(
      service,
      "Status", G_TYPE_BOOLEAN, status,
      NULL);

    // Quiet means that action will be executed w/o print.
    if (!quiet)
    {
      g_print("The device is now %s.\n", status ? "on" : "off");
    }
  }

  /* Return success to the client */
  g_print("%s: status = %s\n", __FUNCTION__, status ? "on" : "off");
  gupnp_service_action_return (action);
}

/* GetTarget */
G_MODULE_EXPORT void
get_target_cb(
  G_GNUC_UNUSED GUPnPService *service,
  GUPnPServiceAction *action,
  G_GNUC_UNUSED gpointer user_data)
{
  gupnp_service_action_set(
    action, "RetTargetValue", G_TYPE_BOOLEAN, status, NULL);
  g_print("%s: status = %s\n", __FUNCTION__, status ? "on" : "off");
  gupnp_service_action_return(action);
}

/* GetStatus */
G_MODULE_EXPORT void
get_status_cb(
  G_GNUC_UNUSED GUPnPService *service,
  GUPnPServiceAction *action,
  G_GNUC_UNUSED gpointer user_data)
{
  gupnp_service_action_set(
    action, "ResultStatus", G_TYPE_BOOLEAN, status, NULL);
  g_print("%s: status = %s\n", __FUNCTION__, status ? "on" : "off");
  gupnp_service_action_return(action);
}

/*
 * State Variable query handlers
 */

/* Target */
G_MODULE_EXPORT void
query_target_cb(
  G_GNUC_UNUSED GUPnPService *service,
  G_GNUC_UNUSED char *variable,
  GValue *value,
  G_GNUC_UNUSED gpointer user_data)
{
  g_value_init(value, G_TYPE_BOOLEAN);
  g_value_set_boolean(value, status);
  g_print("%s: status = %s\n", __FUNCTION__, status ? "on" : "off");
}

/* Status */
G_MODULE_EXPORT void
query_status_cb(
  G_GNUC_UNUSED GUPnPService *service,
  G_GNUC_UNUSED char *variable,
  GValue *value,
  G_GNUC_UNUSED gpointer user_data)
{
  g_value_init(value, G_TYPE_BOOLEAN);
  g_value_set_boolean(value, status);
  g_print("%s: status = %s\n", __FUNCTION__, status ? "on" : "off");
}

int
main(
  G_GNUC_UNUSED int argc,
  G_GNUC_UNUSED char **argv)
{
  GOptionContext *optionContext;
  GMainLoop *main_loop;
  GError *error = NULL;
  GUPnPContext *context;
  GUPnPRootDevice *dev;
  GUPnPServiceInfo *service;

  // Try to get option argument.
  optionContext = g_option_context_new(NULL);
  g_option_context_add_main_entries(optionContext, entries, NULL);
  if (!g_option_context_parse(optionContext, &argc, &argv, &error))
  {
    g_print("option parsing failed: %s\n", error->message);
    exit(EXIT_FAILURE);
  }

  /* By default the device is off */
  status = FALSE;
  if (!quiet)
  {
    g_print("The device is now %s.\n", status ? "on" : "off");
  }

  /* Create the UPnP context */
  context = gupnp_context_new(NULL, NULL, 0, &error);
  if (error || context == NULL) {
    g_printerr(
      "Error creating the GUPnP context: %s\n", error->message);
    g_error_free(error);
    return EXIT_FAILURE;
  }

  /* Create virtual device */
  dev = gupnp_root_device_new(context, "VirtualDevice.xml", "../xml");
  if (dev == NULL) {
    g_printerr("Error creating the root device\n");
    return EXIT_FAILURE;
  }
  gupnp_root_device_set_available(dev, TRUE);

  /* Get the switch service from the root device */
  service = gupnp_device_info_get_service(
    GUPNP_DEVICE_INFO(dev), "urn:schemas-upnp-org:service:SwitchPower:1");
  if (!service) {
    g_printerr("Cannot get SwitchPower1 service\n");
    return EXIT_FAILURE;
  }
  
  /*
   * Autoconnect the action and state variable handlers.  This connects
   * query_target_cb and query_status_cb to the Target and Status state
   * variables query callbacks, and set_target_cb, get_target_cb and
   * get_status_cb to SetTarget, GetTarget and GetStatus actions respectively.
   */
  gupnp_service_signals_autoconnect(GUPNP_SERVICE(service), NULL, &error);
  if (error) {
    g_printerr("Failed to autoconnect signals: %s\n", error->message);
    g_error_free(error);
    return EXIT_FAILURE;
  }
  
  /* Run the main loop */
  main_loop = g_main_loop_new(NULL, FALSE);
  g_main_loop_run(main_loop);

  /* Cleanup */
  g_main_loop_unref(main_loop);
  g_object_unref(service);
  g_object_unref(dev);
  g_object_unref(context);
  g_object_unref(optionContext);
  
  return EXIT_SUCCESS;
}
