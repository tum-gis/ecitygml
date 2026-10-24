<?xml version="1.0" encoding="UTF-8"?>
<!-- Hand-written, not real data (see README.md): a tunnel with a tunnel part. -->
<CityModel xmlns="http://www.opengis.net/citygml/3.0" xmlns:gml="http://www.opengis.net/gml/3.2" xmlns:con="http://www.opengis.net/citygml/construction/3.0" xmlns:tun="http://www.opengis.net/citygml/tunnel/3.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.opengis.net/citygml/tunnel/3.0 http://schemas.opengis.net/citygml/tunnel/3.0/tunnel.xsd">
  <cityObjectMember>
    <tun:Tunnel gml:id="tunnel_1">
      <gml:name>Synthetic tunnel</gml:name>
      <con:dateOfConstruction>1990-05-01</con:dateOfConstruction>
      <tun:class codeSpace="https://example.org/tunnel_class">1000</tun:class>
      <tun:function>1010</tun:function>
      <tun:function>1020</tun:function>
      <tun:usage>1000</tun:usage>
      <tun:tunnelPart>
        <tun:TunnelPart gml:id="tunnel_part_1">
          <tun:function>1030</tun:function>
        </tun:TunnelPart>
      </tun:tunnelPart>
    </tun:Tunnel>
  </cityObjectMember>
</CityModel>
