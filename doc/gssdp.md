### gssdp

https://github.com/GNOME/gssdp
https://en.wikipedia.org/wiki/Simple_Service_Discovery_Protocol
http://upnp.org/specs/arch/UPnP-arch-DeviceArchitecture-v1.0.pdf

Simple Service Discovery Protocol. A multicast discovery and search mechanism that uses a multicast variant of HTTP over UDP. 

- Packages
  libgssdp-1.0-3 GObject-based library for SSDP

- Interfaces
  - Target
    Target Device
  - USN (Unique Name Service)
    In general constructed with uuid, since this has to be unique.
  - Location
    URI to indicate this service is available and to get xml configuration data.
