#include <libgssdp/gssdp.h>
#include <gio/gio.h>
#include <stdlib.h>

static void
resource_available_cb(
  G_GNUC_UNUSED GSSDPResourceBrowser *resource_browser,
  const char *usn, GList *locations)
{
  GList *l;

  g_print("resource available\n"
           "  USN:      %s\n", usn);

  for (l = locations; l; l = l->next) {
    g_print("  Location: %s\n", (char *) l->data);
  }
}

static void
resource_unavailable_cb(
  G_GNUC_UNUSED GSSDPResourceBrowser *resource_browser,
  const char *usn)
{
  g_print ("resource unavailable\n"
           "  USN:      %s\n", usn);
}

int
main(
  G_GNUC_UNUSED int    argc,
  G_GNUC_UNUSED char **argv)
{
  GSSDPClient *client;
  GSSDPResourceBrowser *resource_browser;
  GError *error;
  GMainLoop *main_loop;

#if !GLIB_CHECK_VERSION (2, 35, 0)
  // Ubuntu18.04.4 2.56.4, so it does not require here.
  g_type_init ();
#endif

  error = NULL;
  // interface will be auto-detected. But it can be specified with "lo".
  client = gssdp_client_new(NULL, NULL, &error);
  if (error || client == NULL) {
    g_printerr("Error creating the GSSDP client: %s\n", error->message);
    g_error_free(error);
    return EXIT_FAILURE;
  }

  // get resource broswer for all resources(ssdp:all).
  resource_browser = gssdp_resource_browser_new(client, GSSDP_ALL_RESOURCES);
  if (resource_browser == NULL) {
    g_printerr("Error creating the GSSDPResourceBrowser associated with client.\n");
    return EXIT_FAILURE;
  }

  // register callbacks via status change.
  /*
   * RESOURCE_AVAILABLE
   * RESOURCE_UNAVAILABLE
   */
  g_signal_connect(resource_browser,
                   "resource-available",
                   G_CALLBACK (resource_available_cb),
                   NULL);
  g_signal_connect(resource_browser,
                   "resource-unavailable",
                   G_CALLBACK (resource_unavailable_cb),
                   NULL);

  // activate the browser now.
  gssdp_resource_browser_set_active(resource_browser, TRUE);

  main_loop = g_main_loop_new(NULL, FALSE);
  g_main_loop_run(main_loop);
  g_main_loop_unref(main_loop);

  // cleanup objects.
  g_object_unref(resource_browser);
  g_object_unref(client);

  return EXIT_SUCCESS;
}
