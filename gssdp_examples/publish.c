#include <libgssdp/gssdp.h>
#include <gio/gio.h>
#include <stdlib.h>

static GMainLoop *main_loop;
static GSSDPResourceGroup *resource_group;

void* thread_function(void *data)
{
  sleep(1);
  // enable service
  g_print("Enable Service: http://127.0.0.1:9999\n");
  gssdp_resource_group_set_available(resource_group, TRUE);

  sleep(5);

  // disbale service
  g_print("Disable Service: http://127.0.0.1:9999\n");
  gssdp_resource_group_set_available(resource_group, FALSE);

  sleep(5);

  // enale service
  g_print("Eable Service: http://127.0.0.1:9999\n");
  gssdp_resource_group_set_available(resource_group, TRUE);

  sleep(5);

  g_main_loop_quit(main_loop); 
  return NULL; 

}

int
main(
  G_GNUC_UNUSED int    argc,
  G_GNUC_UNUSED char **argv)
{
  GSSDPClient *client;
  GError *error;
  GThread *ps_thread;

#if !GLIB_CHECK_VERSION(2, 35, 0)
  // Ubuntu18.04.4 2.56.4, so it does not require here.
  g_type_init();
#endif

  main_loop = g_main_loop_new(NULL, FALSE);

  error = NULL;
  // interface will be auto-detected. But it can be specified with "lo".
  client = gssdp_client_new(NULL, NULL, &error);
  if (error || client == NULL) {
    g_printerr("Error creating the GSSDP client: %s\n", error->message);
    g_error_free(error);
    return EXIT_FAILURE;
  }

  // get resource group associated with client.
  resource_group = gssdp_resource_group_new(client);
  if (resource_group == NULL) {
    g_printerr("Error creating the GSSDPResourceGroup associated with client.\n");
    return EXIT_FAILURE;
  }

  /*
   * uuid is unique idetification for this device.
   * UPnP transmits data via http, this is UPnP(also SSDP) specification.
   */
  gssdp_resource_group_add_resource_simple(
    resource_group,
    "upnp:test:device",
    "uuid:24ba8a98-2da0-4360-9bb3-3014914604a4::upnp:test:device",
    "http://127.0.0.1:9999"); // just for temporary, anything as long as it is text.

  ps_thread = g_thread_new("thread", thread_function, main_loop); 
  g_main_loop_run(main_loop);
  g_main_loop_unref(main_loop);
  
  // clearup objects.
  g_object_unref(resource_group);
  g_object_unref(client);

  return EXIT_SUCCESS;
}
