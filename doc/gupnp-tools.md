### gupnp-tools

https://github.com/GNOME/gupnp-tools

- How to install
  ```
  sudo apt install gupnp-tools
  ```

- Command Line Interfaces
  - ***/usr/bin/gssdp-discover***
  - /usr/bin/gupnp-av-cp
  - /usr/bin/gupnp-network-light
  - /usr/bin/gupnp-universal-cp
  - /usr/bin/gupnp-upload

### Discovery Example

https://github.com/GNOME/gupnp-tools/tree/mainline/src/discover

```
>gssdp-discover -m all -t foo:bar -n 10 -r 1
Using network interface docker0
Scanning for resources matching foo:bar
Showing "all" messages
...<snip>
```

- Network Interface
  - If network interface is not specified, it will be auto-detection.
- Target
  - generic string the resource browser listens for on the SSDP bus.
  - Several possibles below, and it can be arbitrary.
    ```
    <itemizedlist>
      <listitem><para>"ssdp:all" for everything</para></listitem>
      <listitem><para>
        "upnp:rootdevice" for UPnP device entry points, not caring about the
        device type</para></listitem>
      <listitem><para>The UUID of a specific device</para></listitem>
      <listitem><para>Device types such as
      "urn:schemas-upnp-org:device:MediaServer:1"</para></listitem>
      <listitem><para>Service types such as
      "urn:schemas-upnp-org:service:ContentDirectory:1"</para></listitem>
    </itemizedlist>
    ```
- Message Type
  ```
  enum {
          RESOURCE_AVAILABLE,
          RESOURCE_UNAVAILABLE,
          RESOURCE_UPDATE,
          LAST_SIGNAL
  };
  ```
  These messages delivered as signal event, so event notification can be supported.
