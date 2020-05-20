### gupnp

https://github.com/GNOME/gupnp

GUPnP is constructed on GSSDP,

GUPnP implements the UPnP specification: resource announcement and discovery, description, control, event notification, and presentation (GUPnP includes basic web server functionality through libsoup). GUPnP does not include helpers for construction or control of specific standardized resources (e.g. MediaServer); this is left for higher level libraries utilizing the GUPnP framework.

server/client examples are ready as following,

- [server](https://github.com/GNOME/gupnp/blob/mainline/examples/light-server.c)
- [client](https://github.com/GNOME/gupnp/blob/mainline/examples/light-client.c)

#### Server

- Publish root device and service.
- Register actions based on [SwitchPower1.xml](https://github.com/GNOME/gupnp/blob/mainline/examples/SwitchPower1.xml)
- Waiting for the query.

#### Client

- Connect service provided by server.
- on/off/toggle the light switch based on arguments.
