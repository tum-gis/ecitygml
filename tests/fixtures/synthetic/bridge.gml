<?xml version="1.0" encoding="UTF-8"?>
<!-- Hand-written, not real data (see README.md): a bridge with a bridge part. -->
<CityModel xmlns="http://www.opengis.net/citygml/3.0" xmlns:gml="http://www.opengis.net/gml/3.2" xmlns:con="http://www.opengis.net/citygml/construction/3.0" xmlns:brid="http://www.opengis.net/citygml/bridge/3.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.opengis.net/citygml/bridge/3.0 http://schemas.opengis.net/citygml/bridge/3.0/bridge.xsd">
  <cityObjectMember>
    <brid:Bridge gml:id="bridge_1">
      <gml:name>Synthetic bridge</gml:name>
      <con:dateOfConstruction>1990-05-01</con:dateOfConstruction>
      <brid:class codeSpace="https://example.org/bridge_class">1000</brid:class>
      <brid:function>1010</brid:function>
      <brid:function>1020</brid:function>
      <brid:usage>1000</brid:usage>
      <brid:isMovable>true</brid:isMovable>
      <brid:bridgePart>
        <brid:BridgePart gml:id="bridge_part_1">
          <brid:isMovable>false</brid:isMovable>
        </brid:BridgePart>
      </brid:bridgePart>
    </brid:Bridge>
  </cityObjectMember>
</CityModel>
