# gupnp_samples

<img src="https://wiki.gnome.org/Projects/GUPnP?action=AttachFile&do=get&target=gupnp_logo.png" width="300">

GNOME GUPnP Samples and Tutorials

GUPnP is an elegant, object-oriented open source framework for creating UPnP devices and control points, written in C using GObject and libsoup. The GUPnP API is intended to be easy to use, efficient and flexible. It provides the same set of features as libupnp, but shields the developer from most of UPnP's internals.

### Environment

Everything here is based on Ubuntu18.04 base. There would not be much difference but not confirmed on any other platform.

### Components / License

Here in this sample and tutorials focuses on GUPnP, GSSDP and GUPnP-Tools.

| Package | Description | License
| :--- | :--- | :--- |
| GSSDP | implementation resource discovery and announcement over SSDP (Simple Service Discovery Protocol). | LGPLv2 |
| GUPnP | core library, implementation the UPnP specification: resource announcement and discovery, description, control, event notification, and presentation (GUPnP includes basic web server functionality through libsoup). GUPnP does not include helpers for construction or control of specific standardized resources (e.g. MediaServer); this is left for higher level libraries utilizing the GUPnP framework. | LGPLv2 |
| GUPnP-AV | collection of helpers for building AV (audio/video) applications using GUPnP. | LGPLv2 |
| GUPnP-DLNA | small utility library that aims to ease the DLNA-related tasks such as media profile guessing, transcoding to a given profile, etc. | LGPLv2.1 |
| GUPnP-IGD | small client library that can be used to talk to Internet Gateway Devices to request NAT forwarding etc. | LGPLv2.1 |
| GUPnP-Tools | set of utilities and demos to work with UPnP. It includes a generic control point, an AV controller, a network light, an uploader and an SSDP commandline client | GPLv2

### Source Code

- [GSSDP](https://github.com/GNOME/gssdp)
- [GUPnP](https://github.com/GNOME/gupnp)
- [GUPnP-Tools](https://github.com/GNOME/gupnp-tools)

### Insights

- [GSSDP](./doc/gssdp.md)
- [GUPnP](./doc/gupnp.md)
- [GUPnP-Tools](./doc/gupnp-tools.md)

### Samples

#### Required Packages

```
sudo apt install gobject-introspection
sudo apt install libgirepository1.0-dev
sudo apt install valac
```

#### GSSDP Examples

- [gssdp_examples](./gssdp_examples)

```
> cd gssdp_examples
> mkdir build
> cd build
> cmake ..
> make
> ./browser (terminal-1)
> ./publisher (terminal-2)
```

#### GUPnP Examples

- [gupnp_examples](./gupnp_examples)

```
> cd gupnp_examples
> mkdir build
> cd build
> cmake ..
> make
> ./server (terminal-1)
> ./client toggle (terminal-2)
```

### Reference

- [GUPnP Project](https://wiki.gnome.org/Projects/GUPnP)
- [Github Mirror](https://github.com/GNOME)
