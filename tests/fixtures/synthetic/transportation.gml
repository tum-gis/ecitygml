<?xml version="1.0" encoding="UTF-8"?>
<!-- Hand-written, not real data (see README.md): a section with traffic direction and occupancy, and a traffic space with a point and a multi curve with a ring member and an unresolved member. -->
<CityModel xmlns="http://www.opengis.net/citygml/3.0" xmlns:gml="http://www.opengis.net/gml/3.2" xmlns:tran="http://www.opengis.net/citygml/transportation/3.0" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.opengis.net/citygml/transportation/3.0 http://schemas.opengis.net/citygml/transportation/3.0/transportation.xsd">
  <cityObjectMember>
    <tran:Road gml:id="road_1">
      <tran:section>
        <tran:Section gml:id="section_1">
          <tran:trafficDirection>both</tran:trafficDirection>
          <tran:occupancy>
            <Occupancy>
              <numberOfOccupants>120</numberOfOccupants>
              <interval>peakHour</interval>
            </Occupancy>
          </tran:occupancy>
          <tran:trafficSpace>
            <tran:TrafficSpace gml:id="space_1">
              <lod0Point>
                <gml:Point gml:id="point_1">
                  <gml:pos>1.5 -2.5 3.25</gml:pos>
                </gml:Point>
              </lod0Point>
              <lod0MultiCurve>
                <gml:MultiCurve>
                  <gml:curveMember>
                    <gml:LineString>
                      <gml:posList>0 0 0 3 4 0</gml:posList>
                    </gml:LineString>
                  </gml:curveMember>
                  <gml:curveMember>
                    <gml:LinearRing>
                      <gml:posList>0 0 0 1 0 0 1 1 0 0 0 0</gml:posList>
                    </gml:LinearRing>
                  </gml:curveMember>
                  <gml:curveMember xlink:href="#missing_curve"/>
                </gml:MultiCurve>
              </lod0MultiCurve>
              <tran:granularity>lane</tran:granularity>
            </tran:TrafficSpace>
          </tran:trafficSpace>
        </tran:Section>
      </tran:section>
    </tran:Road>
  </cityObjectMember>
</CityModel>
