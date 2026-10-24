<?xml version="1.0" encoding="UTF-8"?>
<!-- Hand-written, not real data (see README.md): two solitary vegetation objects with implicit geometries and a plant cover. -->
<CityModel xmlns="http://www.opengis.net/citygml/3.0" xmlns:gml="http://www.opengis.net/gml/3.2" xmlns:veg="http://www.opengis.net/citygml/vegetation/3.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.opengis.net/citygml/vegetation/3.0 http://schemas.opengis.net/citygml/vegetation/3.0/vegetation.xsd">
  <cityObjectMember>
    <veg:SolitaryVegetationObject gml:id="tree_1">
      <lod1ImplicitRepresentation>
        <ImplicitGeometry gml:id="tree_prototype">
          <transformationMatrix>2 0 0 10 0 2 0 20 0 0 3 30 0 0 0 1</transformationMatrix>
          <mimeType>model/gltf+json</mimeType>
          <referencePoint>
            <gml:Point>
              <gml:pos>457850 5439090 112</gml:pos>
            </gml:Point>
          </referencePoint>
          <relativeGeometry>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon>
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:posList>0 0 0 1 0 0 1 1 0 0 0 0</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </relativeGeometry>
        </ImplicitGeometry>
      </lod1ImplicitRepresentation>
      <veg:class codeSpace="https://example.org/tree_class">1000</veg:class>
      <veg:function>1010</veg:function>
      <veg:usage>1020</veg:usage>
      <veg:species>Quercus robur</veg:species>
      <veg:height uom="m">12.5</veg:height>
      <veg:trunkDiameter uom="m">0.4</veg:trunkDiameter>
      <veg:crownDiameter uom="m">5.5</veg:crownDiameter>
      <veg:rootBallDiameter uom="m">1.2</veg:rootBallDiameter>
      <veg:maxRootBallDepth uom="m">0.8</veg:maxRootBallDepth>
    </veg:SolitaryVegetationObject>
  </cityObjectMember>
  <cityObjectMember>
    <veg:SolitaryVegetationObject gml:id="tree_2">
      <lod2ImplicitRepresentation>
        <ImplicitGeometry gml:id="point_prototype">
          <transformationMatrix>1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1</transformationMatrix>
          <libraryObject>https://example.org/trees/oak.gltf</libraryObject>
          <referencePoint>
            <gml:Point>
              <gml:pos>457860 5439095 112</gml:pos>
            </gml:Point>
          </referencePoint>
          <relativeGeometry>
            <gml:Point>
              <gml:pos>0 0 0</gml:pos>
            </gml:Point>
          </relativeGeometry>
        </ImplicitGeometry>
      </lod2ImplicitRepresentation>
    </veg:SolitaryVegetationObject>
  </cityObjectMember>
  <cityObjectMember>
    <veg:PlantCover gml:id="cover_1">
      <veg:class>2000</veg:class>
      <veg:averageHeight uom="m">2.5</veg:averageHeight>
      <veg:minHeight uom="m">1</veg:minHeight>
      <veg:maxHeight uom="m">4</veg:maxHeight>
    </veg:PlantCover>
  </cityObjectMember>
</CityModel>
