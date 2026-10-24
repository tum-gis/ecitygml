<?xml version="1.0" encoding="UTF-8"?>
<!-- Hand-written, not real data (see README.md): the city object, physical space and construction properties no real fixture has. -->
<CityModel xmlns="http://www.opengis.net/citygml/3.0" xmlns:gml="http://www.opengis.net/gml/3.2" xmlns:con="http://www.opengis.net/citygml/construction/3.0" xmlns:bldg="http://www.opengis.net/citygml/building/3.0" xmlns:gen="http://www.opengis.net/citygml/generics/3.0" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.opengis.net/citygml/building/3.0 http://schemas.opengis.net/citygml/building/3.0/building.xsd http://www.opengis.net/citygml/generics/3.0 http://schemas.opengis.net/citygml/generics/3.0/generics.xsd">
  <cityObjectMember>
    <bldg:Building gml:id="building_1">
      <relativeToTerrain>entirelyAboveTerrain</relativeToTerrain>
      <relativeToWater>entirelyAboveWaterSurface</relativeToWater>
      <relatedTo>
        <CityObjectRelation>
          <genericAttribute>
            <gen:IntAttribute>
              <gen:name>weight</gen:name>
              <gen:value>3</gen:value>
            </gen:IntAttribute>
          </genericAttribute>
          <relationType>shared</relationType>
          <relatedTo xlink:href="#building_2"/>
        </CityObjectRelation>
      </relatedTo>
      <genericAttribute>
        <gen:GenericAttributeSet>
          <gen:name>energy</gen:name>
          <gen:genericAttribute>
            <gen:DoubleAttribute>
              <gen:name>demand</gen:name>
              <gen:value>12.5</gen:value>
            </gen:DoubleAttribute>
          </gen:genericAttribute>
          <gen:genericAttribute>
            <gen:StringAttribute>
              <gen:name>label</gen:name>
              <gen:value>A+</gen:value>
            </gen:StringAttribute>
          </gen:genericAttribute>
        </gen:GenericAttributeSet>
      </genericAttribute>
      <boundary>
        <con:RoofSurface gml:id="roof_1">
          <con:fillingSurface>
            <con:WindowSurface gml:id="roof_window_1"/>
          </con:fillingSurface>
        </con:RoofSurface>
      </boundary>
      <boundary xlink:href="#missing_boundary"/>
      <lod2TerrainIntersectionCurve>
        <gml:MultiCurve>
          <gml:curveMember>
            <gml:LineString>
              <gml:posList>457842 5439083 111.8 457854 5439083 111.8</gml:posList>
            </gml:LineString>
          </gml:curveMember>
        </gml:MultiCurve>
      </lod2TerrainIntersectionCurve>
      <con:dateOfConstruction>2020-01-01</con:dateOfConstruction>
      <con:dateOfDemolition>2050-12-31</con:dateOfDemolition>
      <con:occupancy>
        <Occupancy>
          <numberOfOccupants>4</numberOfOccupants>
          <interval>daytime</interval>
          <occupantType>residents</occupantType>
        </Occupancy>
      </con:occupancy>
    </bldg:Building>
  </cityObjectMember>
  <cityObjectMember>
    <bldg:Building gml:id="building_2"/>
  </cityObjectMember>
</CityModel>
