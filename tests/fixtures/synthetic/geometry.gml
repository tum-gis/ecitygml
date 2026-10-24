<?xml version="1.0" encoding="UTF-8"?>
<!-- Hand-written, not real data (see README.md): surface members that triangulate unusually. -->
<CityModel xmlns="http://www.opengis.net/citygml/3.0" xmlns:gml="http://www.opengis.net/gml/3.2" xmlns:bldg="http://www.opengis.net/citygml/building/3.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.opengis.net/citygml/building/3.0 http://schemas.opengis.net/citygml/building/3.0/building.xsd">
  <cityObjectMember>
    <bldg:Building gml:id="geometry_1">
      <lod2MultiSurface>
        <gml:MultiSurface>
          <gml:surfaceMember>
            <gml:Polygon gml:id="square">
              <gml:exterior>
                <gml:LinearRing>
                  <gml:posList>0 0 1 1 0 1 1 1 1 0 1 1 0 0 1</gml:posList>
                </gml:LinearRing>
              </gml:exterior>
            </gml:Polygon>
          </gml:surfaceMember>
          <gml:surfaceMember>
            <gml:Polygon gml:id="collinear">
              <gml:exterior>
                <gml:LinearRing>
                  <gml:posList>0 0 9 1 0 9 2 0 9 3 0 9 0 0 9</gml:posList>
                </gml:LinearRing>
              </gml:exterior>
            </gml:Polygon>
          </gml:surfaceMember>
          <gml:surfaceMember>
            <gml:TriangulatedSurface gml:id="tin">
              <gml:patches>
                <gml:Triangle>
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:posList>0 0 6 1 0 6 1 1 6 0 0 6</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Triangle>
                <gml:Triangle>
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:posList>0 0 7 1 0 7 1 1 7 0 0 7</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Triangle>
              </gml:patches>
            </gml:TriangulatedSurface>
          </gml:surfaceMember>
        </gml:MultiSurface>
      </lod2MultiSurface>
    </bldg:Building>
  </cityObjectMember>
</CityModel>
