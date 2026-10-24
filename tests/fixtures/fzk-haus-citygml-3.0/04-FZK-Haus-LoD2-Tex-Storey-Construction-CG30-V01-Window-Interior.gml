<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<!-- 2023-02-14 KHH / IAI Mannually converted to CityGML 3.0  -->
<!-- This CityGML model is made for testing CityGML Version 3.0 by KHH from the Institut for Automation and Applied Informatics (IAI) at Karlsruhe Institute of Technology (KIT) -->
<!-- If you use this CityGML model for publication, please refer to the Institut for Automation and Applied Informatics (IAI) at Karlsruhe Institute of Technology (KIT) -->
<!-- This model is made using Sketchup with CityEditor (3DIS GmbH), CityGML-Tools (VCS), CloudCompare and manual work -->
<core:CityModel xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xmlns:con="http://www.opengis.net/citygml/construction/3.0"
  xmlns:core="http://www.opengis.net/citygml/3.0" xmlns:xlink="http://www.w3.org/1999/xlink"
  xmlns:gml="http://www.opengis.net/gml/3.2"
  xmlns:bldg="http://www.opengis.net/citygml/building/3.0"
  xmlns:app="http://www.opengis.net/citygml/appearance/3.0"
  xmlns:pcl="http://www.opengis.net/citygml/pointcloud/3.0"
  xmlns:gen="http://www.opengis.net/citygml/generics/3.0" xmlns:xAL="urn:oasis:names:tc:ciq:xal:3"
  xsi:schemaLocation="http://www.opengis.net/citygml/3.0 https://sdm-web.cloud.iai.kit.edu/CityGML-3-0/Schema/core.xsd 
  http://www.opengis.net/citygml/appearance/3.0 https://sdm-web.cloud.iai.kit.edu/CityGML-3-0/Schema/appearance.xsd 
  http://www.opengis.net/citygml/bridge/3.0 https://sdm-web.cloud.iai.kit.edu/CityGML-3-0/Schema/bridge.xsd 
  http://www.opengis.net/citygml/building/3.0 https://sdm-web.cloud.iai.kit.edu/CityGML-3-0/Schema/building.xsd
  http://www.opengis.net/citygml/cityfurniture/3.0 https://sdm-web.cloud.iai.kit.edu/CityGML-3-0/Schema/cityFurniture.xsd
  http://www.opengis.net/citygml/cityobjectgroup/3.0 https://sdm-web.cloud.iai.kit.edu/CityGML-3-0/Schema/cityObjectGroup.xsd
  http://www.opengis.net/citygml/generics/3.0 https://sdm-web.cloud.iai.kit.edu/CityGML-3-0/Schema/generics.xsd 
  http://www.opengis.net/citygml/landuse/3.0 https://sdm-web.cloud.iai.kit.edu/CityGML-3-0/Schema/landUse.xsd 
  http://www.opengis.net/citygml/relief/3.0 https://sdm-web.cloud.iai.kit.edu/CityGML-3-0/Schema/relief.xsd 
  http://www.opengis.net/citygml/transportation/3.0 https://sdm-web.cloud.iai.kit.edu/CityGML-3-0/Schema/transportation.xsd
  http://www.opengis.net/citygml/tunnel/3.0 https://sdm-web.cloud.iai.kit.edu/CityGML-3-0/Schema/tunnel.xsd
  http://www.opengis.net/citygml/pointcloud/3.0 https://sdm-web.cloud.iai.kit.edu/CityGML-3-0/Schema/pointCloud.xsd 
  http://www.opengis.net/citygml/vegetation/3.0 https://sdm-web.cloud.iai.kit.edu/CityGML-3-0/Schema/vegetation.xsd 
  http://www.opengis.net/citygml/waterbody/3.0 https://sdm-web.cloud.iai.kit.edu/CityGML-3-0/Schema/waterBody.xsd">
  <gml:description>KIT Test Building FZK-Haus adapted for CityGML 3.0</gml:description>
  <gml:name>KIT CityGML Version 3.0 Models</gml:name>
  <gml:boundedBy>
    <gml:Envelope srsName="EPSG:25832" srsDimension="3">
      <gml:lowerCorner>458899.5 5438784.5 113.5</gml:lowerCorner>
      <gml:upperCorner>458912.5 5438795.5 120.017691</gml:upperCorner>
    </gml:Envelope>
  </gml:boundedBy>
  <core:cityObjectMember>
    <bldg:Building gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz">
      <gml:description>KIT FZK-Haus outer shell as constructions, storeys, windows and interior constructions</gml:description>
      <gml:name>KIT FZK-Haus</gml:name>
      <con:conditionOfConstruction>projected</con:conditionOfConstruction>
      <con:height>
        <con:Height>
          <con:highReference>highestRoofEdge</con:highReference>
          <con:lowReference>lowestGroundPoint</con:lowReference>
          <con:status>measured</con:status>
          <con:value uom="urn:adv:uom:m">6.52</con:value>
        </con:Height>
      </con:height>
      <con:occupancy>
        <core:Occupancy>
          <core:numberOfOccupants>2</core:numberOfOccupants>
        </core:Occupancy>
      </con:occupancy>
      <bldg:function codeSpace="https://sdm-web.cloud.iai.kit.edu/data/codelists/BuildingFunctionTypeAdV-trans.xml">31001_1000</bldg:function>
      <bldg:roofType codeSpace="https://sdm-web.cloud.iai.kit.edu/data/codelists/RoofTypeTypeAdV-trans.xml">3100</bldg:roofType>
      <bldg:buildingSubdivision>
        <bldg:Storey>
          <gml:name>Ground Floor</gml:name>
          <bldg:class>Entrance Floor</bldg:class>
          <bldg:buildingConstructiveElement>
            <bldg:BuildingConstructiveElement
              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj">
              <gml:name>01 - Ground Floor Ground plate</gml:name>
              <core:lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_PG.xJxsIZemRugiHB0gL5h6">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438785.0 113.5 458900.0
                                5438785.0 113.5 458900.0 5438795.0 113.5 458912.0 5438795.0 113.5
                                458912.0 5438785.0 113.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_PG.QOcD5lDTtfLZxmwl1Zwu">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438785.0 113.7 458912.0
                                5438785.0 113.7 458912.0 5438795.0 113.7 458900.0 5438795.0 113.7
                                458900.0 5438785.0 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_PG.e9AMeV0pEURTngbpCIid">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_LR.1wtpWcM1ybr7En9jkc48">
                              <gml:posList srsDimension="3">458900.0 5438795.0 113.5 458900.0
                                5438795.0 113.7 458912.0 5438795.0 113.7 458912.0 5438795.0 113.5
                                458900.0 5438795.0 113.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_PG.hNmG4YmoXQMBm8b42JJ4">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_LR.8mE1jXWCpsO6DUwaB6i7">
                              <gml:posList srsDimension="3">458912.0 5438795.0 113.5 458912.0
                                5438795.0 113.7 458912.0 5438785.0 113.7 458912.0 5438785.0 113.5
                                458912.0 5438795.0 113.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_PG.vgpO7agF1kI7rJRF6jCg">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_LR.N0N0IsKBdvpy39boJBww">
                              <gml:posList srsDimension="3">458912.0 5438785.0 113.5 458912.0
                                5438785.0 113.7 458900.0 5438785.0 113.7 458900.0 5438785.0 113.5
                                458912.0 5438785.0 113.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_PG.MgxBTndXeCqtGtBjgXrT">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_LR.fGwcpAcL6rIhCv6OIXnh">
                              <gml:posList srsDimension="3">458900.0 5438785.0 113.5 458900.0
                                5438785.0 113.7 458900.0 5438795.0 113.7 458900.0 5438795.0 113.5
                                458900.0 5438785.0 113.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </core:lod2Solid>
              <con:isStructuralElement>true</con:isStructuralElement>
              <bldg:class>Slab</bldg:class>
            </bldg:BuildingConstructiveElement>
          </bldg:buildingConstructiveElement>
          <bldg:buildingConstructiveElement>
            <bldg:BuildingConstructiveElement
              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY">
              <gml:name>02 - Ground Floor Wall North</gml:name>
              <core:lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.NuNgbvh89KUaU7XcKYUI">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438795.0 113.7 458900.3
                                5438794.7 113.7 458900.3 5438794.7 116.4 458900.0 5438795.0 116.4
                                458900.0 5438795.0 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.SkQ1rqOSiiV6z6rQY7GU">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438794.7 113.7 458900.3
                                5438794.7 113.7 458900.0 5438795.0 113.7 458912.0 5438795.0 113.7
                                458911.7 5438794.7 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.7lmPQ81QGPKvuCTrEOSx">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438794.7 116.4 458911.7
                                5438794.7 116.4 458912.0 5438795.0 116.4 458900.0 5438795.0 116.4
                                458900.3 5438794.7 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.Kwmv6nB3tfpmhbXAL7nY">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438794.7 113.7 458912.0
                                5438795.0 113.7 458912.0 5438795.0 116.4 458911.7 5438794.7 116.4
                                458911.7 5438794.7 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.IcNXv53aAiAf2cDQC2Ew">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438794.7 116.4 458900.3
                                5438794.7 113.7 458911.7 5438794.7 113.7 458911.7 5438794.7 116.4
                                458900.3 5438794.7 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                          <gml:interior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458910.795 5438794.7 114.5 458908.795
                                5438794.7 114.5 458908.795 5438794.7 115.7 458910.795 5438794.7
                                115.7 458910.795 5438794.7 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                          <gml:interior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458906.66 5438794.7 114.5 458904.66
                                5438794.7 114.5 458904.66 5438794.7 115.7 458906.66 5438794.7 115.7
                                458906.66 5438794.7 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                          <gml:interior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.05 5438794.7 114.5 458901.05
                                5438794.7 114.5 458901.05 5438794.7 115.7 458903.05 5438794.7 115.7
                                458903.05 5438794.7 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.GhhgkoiACRoutZj6gPJD">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_LR.rJ8039v7rlqStEtLP060">
                              <gml:posList srsDimension="3">458912.0 5438795.0 116.4 458912.0
                                5438795.0 113.7 458900.0 5438795.0 113.7 458900.0 5438795.0 116.4
                                458912.0 5438795.0 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                          <gml:interior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_LR.qYUpaoqvi5HuqJtc70xY">
                              <gml:posList srsDimension="3">458908.795 5438795.0 114.5 458910.795
                                5438795.0 114.5 458910.795 5438795.0 115.7 458908.795 5438795.0
                                115.7 458908.795 5438795.0 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                          <gml:interior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_LR.BEQS7EgIBnVnvbagopYh">
                              <gml:posList srsDimension="3">458904.66 5438795.0 114.5 458906.66
                                5438795.0 114.5 458906.66 5438795.0 115.7 458904.66 5438795.0 115.7
                                458904.66 5438795.0 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                          <gml:interior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_LR.fm520RqpNLcjtkZnu7G7">
                              <gml:posList srsDimension="3">458901.05 5438795.0 114.5 458903.05
                                5438795.0 114.5 458903.05 5438795.0 115.7 458901.05 5438795.0 115.7
                                458901.05 5438795.0 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.MVOQRduYfbqKfESybtGu">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458910.795 5438795.0 114.5 458908.795
                                5438795.0 114.5 458908.795 5438794.7 114.5 458910.795 5438794.7
                                114.5 458910.795 5438795.0 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.PIfvzvWWSzYur9lPkacC">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458908.795 5438795.0 114.5 458908.795
                                5438795.0 115.7 458908.795 5438794.7 115.7 458908.795 5438794.7
                                114.5 458908.795 5438795.0 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.FqtCUBIfZ5bxz3316yiW">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458908.795 5438795.0 115.7 458910.795
                                5438795.0 115.7 458910.795 5438794.7 115.7 458908.795 5438794.7
                                115.7 458908.795 5438795.0 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.NpYKpOGWkPe9lowTp47V">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458910.795 5438795.0 115.7 458910.795
                                5438795.0 114.5 458910.795 5438794.7 114.5 458910.795 5438794.7
                                115.7 458910.795 5438795.0 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.lfroSmlAjpjCdP0N6iKD">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458906.66 5438795.0 114.5 458904.66
                                5438795.0 114.5 458904.66 5438794.7 114.5 458906.66 5438794.7 114.5
                                458906.66 5438795.0 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.lSWao7HQmKNrbs6PnU2K">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458904.66 5438795.0 114.5 458904.66
                                5438795.0 115.7 458904.66 5438794.7 115.7 458904.66 5438794.7 114.5
                                458904.66 5438795.0 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.Va6PI4eI8VJzLeR5y7tC">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458904.66 5438795.0 115.7 458906.66
                                5438795.0 115.7 458906.66 5438794.7 115.7 458904.66 5438794.7 115.7
                                458904.66 5438795.0 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.EXAhFSCfswxY804ozzBf">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458906.66 5438795.0 115.7 458906.66
                                5438795.0 114.5 458906.66 5438794.7 114.5 458906.66 5438794.7 115.7
                                458906.66 5438795.0 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.D5CMrrjCZQy3x6jkPXKE">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.05 5438795.0 114.5 458901.05
                                5438795.0 114.5 458901.05 5438794.7 114.5 458903.05 5438794.7 114.5
                                458903.05 5438795.0 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.cms7HTJt4aS9N3WWAlmD">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458901.05 5438795.0 114.5 458901.05
                                5438795.0 115.7 458901.05 5438794.7 115.7 458901.05 5438794.7 114.5
                                458901.05 5438795.0 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.2xepsHwio6EWFmZNT1Jx">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458901.05 5438795.0 115.7 458903.05
                                5438795.0 115.7 458903.05 5438794.7 115.7 458901.05 5438794.7 115.7
                                458901.05 5438795.0 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.DBX6vx2V6CrFOGig4PUo">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.05 5438795.0 115.7 458903.05
                                5438795.0 114.5 458903.05 5438794.7 114.5 458903.05 5438794.7 115.7
                                458903.05 5438795.0 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </core:lod2Solid>
              <con:isStructuralElement>true</con:isStructuralElement>
              <con:filling>
                <con:Window
                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.Wi0ORs5kGMnKQlfhDaYi">
                  <gml:name>15 - Ground Floor Window01 North</gml:name>
                  <core:lod2Solid>
                    <gml:Solid>
                      <gml:exterior>
                        <gml:Shell>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458908.795 5438794.7 114.5
                                    458910.795 5438794.7 114.5 458910.795 5438794.7 115.7 458908.795
                                    5438794.7 115.7 458908.795 5438794.7 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458910.795 5438794.7 114.5
                                    458910.795 5438795.0 114.5 458910.795 5438795.0 115.7 458910.795
                                    5438794.7 115.7 458910.795 5438794.7 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458908.795 5438795.0 115.7
                                    458908.795 5438794.7 115.7 458910.795 5438794.7 115.7 458910.795
                                    5438795.0 115.7 458908.795 5438795.0 115.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458908.795 5438794.7 114.5
                                    458908.795 5438795.0 114.5 458910.795 5438795.0 114.5 458910.795
                                    5438794.7 114.5 458908.795 5438794.7 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.Wi0ORs5kGMnKQlfhDaYi_PG.TOVTlyvimFvgR5oiaBXV">
                              <gml:exterior>
                                <gml:LinearRing
                                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.Wi0ORs5kGMnKQlfhDaYi_LR.0eYV408FAjRuy4cttZmh">
                                  <gml:posList srsDimension="3">458910.795 5438795.0 114.5
                                    458908.795 5438795.0 114.5 458908.795 5438795.0 115.7 458910.795
                                    5438795.0 115.7 458910.795 5438795.0 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458908.795 5438795.0 114.5
                                    458908.795 5438794.7 114.5 458908.795 5438794.7 115.7 458908.795
                                    5438795.0 115.7 458908.795 5438795.0 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                        </gml:Shell>
                      </gml:exterior>
                    </gml:Solid>
                  </core:lod2Solid>
                </con:Window>
              </con:filling>
              <con:filling>
                <con:Window
                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.BrpRZ0nUpEXSyByeHjSs">
                  <gml:name>24 - Ground Floor Window02 North</gml:name>
                  <core:lod2Solid>
                    <gml:Solid>
                      <gml:exterior>
                        <gml:Shell>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458906.66 5438794.7 114.5 458906.66
                                    5438795.0 114.5 458906.66 5438795.0 115.7 458906.66 5438794.7
                                    115.7 458906.66 5438794.7 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458904.66 5438795.0 114.5 458904.66
                                    5438794.7 114.5 458904.66 5438794.7 115.7 458904.66 5438795.0
                                    115.7 458904.66 5438795.0 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.BrpRZ0nUpEXSyByeHjSs_PG.JGb8xPG9HlFIsgBWPU4U">
                              <gml:exterior>
                                <gml:LinearRing
                                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.BrpRZ0nUpEXSyByeHjSs_LR.xkPmtBFpsnKTartUJOsW">
                                  <gml:posList srsDimension="3">458906.66 5438795.0 114.5 458904.66
                                    5438795.0 114.5 458904.66 5438795.0 115.7 458906.66 5438795.0
                                    115.7 458906.66 5438795.0 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458904.66 5438794.7 114.5 458906.66
                                    5438794.7 114.5 458906.66 5438794.7 115.7 458904.66 5438794.7
                                    115.7 458904.66 5438794.7 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458904.66 5438795.0 115.7 458904.66
                                    5438794.7 115.7 458906.66 5438794.7 115.7 458906.66 5438795.0
                                    115.7 458904.66 5438795.0 115.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458906.66 5438795.0 114.5 458906.66
                                    5438794.7 114.5 458904.66 5438794.7 114.5 458904.66 5438795.0
                                    114.5 458906.66 5438795.0 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                        </gml:Shell>
                      </gml:exterior>
                    </gml:Solid>
                  </core:lod2Solid>
                </con:Window>
              </con:filling>
              <con:filling>
                <con:Window
                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.4hdRTFC3hEyX9Ur6AK11">
                  <gml:name>21 - Ground Floor Window03 North</gml:name>
                  <core:lod2Solid>
                    <gml:Solid>
                      <gml:exterior>
                        <gml:Shell>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458901.05 5438794.7 114.5 458903.05
                                    5438794.7 114.5 458903.05 5438794.7 115.7 458901.05 5438794.7
                                    115.7 458901.05 5438794.7 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458901.05 5438795.0 115.7 458901.05
                                    5438794.7 115.7 458903.05 5438794.7 115.7 458903.05 5438795.0
                                    115.7 458901.05 5438795.0 115.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458901.05 5438795.0 114.5 458901.05
                                    5438794.7 114.5 458901.05 5438794.7 115.7 458901.05 5438795.0
                                    115.7 458901.05 5438795.0 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458903.05 5438794.7 114.5 458903.05
                                    5438795.0 114.5 458903.05 5438795.0 115.7 458903.05 5438794.7
                                    115.7 458903.05 5438794.7 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458903.05 5438795.0 114.5 458903.05
                                    5438794.7 114.5 458901.05 5438794.7 114.5 458901.05 5438795.0
                                    114.5 458903.05 5438795.0 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.4hdRTFC3hEyX9Ur6AK11_PG.QxXXZUcYDSPgAvfml3o9">
                              <gml:exterior>
                                <gml:LinearRing
                                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.4hdRTFC3hEyX9Ur6AK11_LR.poSQunJA2uWxlLFqMgdz">
                                  <gml:posList srsDimension="3">458903.05 5438795.0 114.5 458901.05
                                    5438795.0 114.5 458901.05 5438795.0 115.7 458903.05 5438795.0
                                    115.7 458903.05 5438795.0 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                        </gml:Shell>
                      </gml:exterior>
                    </gml:Solid>
                  </core:lod2Solid>
                </con:Window>
              </con:filling>
              <bldg:class>Wall</bldg:class>
            </bldg:BuildingConstructiveElement>
          </bldg:buildingConstructiveElement>
          <bldg:buildingConstructiveElement>
            <bldg:BuildingConstructiveElement
              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8">
              <gml:name>03 - Ground Floor Wall East</gml:name>
              <core:lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.sOAjMic9c7isncdb0L83">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438794.7 113.7 458911.7
                                5438794.7 116.4 458912.0 5438795.0 116.4 458912.0 5438795.0 113.7
                                458911.7 5438794.7 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.98yMmpoQXs5BB8nXxfG9">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438785.3 113.7 458911.7
                                5438794.7 113.7 458912.0 5438795.0 113.7 458912.0 5438785.0 113.7
                                458911.7 5438785.3 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.UESzjRItWh3clkyc6Hgz">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438794.7 116.4 458911.7
                                5438785.3 116.4 458912.0 5438785.0 116.4 458912.0 5438795.0 116.4
                                458911.7 5438794.7 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.yoLDnur9D7wsl8xB8Gj0">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438785.3 113.7 458912.0
                                5438785.0 113.7 458912.0 5438785.0 116.4 458911.7 5438785.3 116.4
                                458911.7 5438785.3 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.3MFcfHVPs9BGmyzDAVgg">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438794.7 116.4 458911.7
                                5438794.7 113.7 458911.7 5438785.3 113.7 458911.7 5438785.3 116.4
                                458911.7 5438794.7 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                          <gml:interior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438791.502394 114.5 458911.7
                                5438793.502394 114.5 458911.7 5438793.502394 115.7 458911.7
                                5438791.502394 115.7 458911.7 5438791.502394 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                          <gml:interior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438786.205 114.5 458911.7
                                5438788.205 114.5 458911.7 5438788.205 115.7 458911.7 5438786.205
                                115.7 458911.7 5438786.205 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.vPkHyW4ZqK4NBbln6BPU">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_LR.LgPfu2laSzYqIXLAF7BV">
                              <gml:posList srsDimension="3">458912.0 5438785.0 116.4 458912.0
                                5438785.0 113.7 458912.0 5438795.0 113.7 458912.0 5438795.0 116.4
                                458912.0 5438785.0 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                          <gml:interior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_LR.AGuJLjkgatzZDk21NVwj">
                              <gml:posList srsDimension="3">458912.0 5438788.205 114.5 458912.0
                                5438786.205 114.5 458912.0 5438786.205 115.7 458912.0 5438788.205
                                115.7 458912.0 5438788.205 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                          <gml:interior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_LR.RvQaGjIjyCTOYZmGhbt8">
                              <gml:posList srsDimension="3">458912.0 5438793.502394 114.5 458912.0
                                5438791.502394 114.5 458912.0 5438791.502394 115.7 458912.0
                                5438793.502394 115.7 458912.0 5438793.502394 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.oGvYxDaN7tEMUBruq989">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_LR.JHgH5G87cusRnbQpajza">
                              <gml:posList srsDimension="3">458912.0 5438791.502394 114.5 458912.0
                                5438793.502394 114.5 458911.7 5438793.502394 114.5 458911.7
                                5438791.502394 114.5 458912.0 5438791.502394 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.aaC58mJm7tRYJrf71O1t">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_LR.rbP3MGxybQWYJ7opJa9n">
                              <gml:posList srsDimension="3">458912.0 5438793.502394 114.5 458912.0
                                5438793.502394 115.7 458911.7 5438793.502394 115.7 458911.7
                                5438793.502394 114.5 458912.0 5438793.502394 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.A5iro2UuhcRvA0U5UnAX">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_LR.TXCGVauXlyCDP9k0qMoL">
                              <gml:posList srsDimension="3">458912.0 5438793.502394 115.7 458912.0
                                5438791.502394 115.7 458911.7 5438791.502394 115.7 458911.7
                                5438793.502394 115.7 458912.0 5438793.502394 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.1p4KTXynAoyl6e166LeS">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_LR.zuGJ76CqDa57IST5SFYT">
                              <gml:posList srsDimension="3">458912.0 5438791.502394 115.7 458912.0
                                5438791.502394 114.5 458911.7 5438791.502394 114.5 458911.7
                                5438791.502394 115.7 458912.0 5438791.502394 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.GN8DA1oDOnCUrimftzTj">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438786.205 114.5 458912.0
                                5438788.205 114.5 458911.7 5438788.205 114.5 458911.7 5438786.205
                                114.5 458912.0 5438786.205 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.KcjNlHb2379iNGJW8tBO">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_LR.FjUf4zY9eRnPtN43qKXo">
                              <gml:posList srsDimension="3">458912.0 5438788.205 114.5 458912.0
                                5438788.205 115.7 458911.7 5438788.205 115.7 458911.7 5438788.205
                                114.5 458912.0 5438788.205 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.wTrfNM4Oxh3XEeBTCyf9">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_LR.3yDBa9Gz2I1KaDiLcUBV">
                              <gml:posList srsDimension="3">458912.0 5438788.205 115.7 458912.0
                                5438786.205 115.7 458911.7 5438786.205 115.7 458911.7 5438788.205
                                115.7 458912.0 5438788.205 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.Y7BpEs72xSPbGra4QPxW">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438786.205 115.7 458912.0
                                5438786.205 114.5 458911.7 5438786.205 114.5 458911.7 5438786.205
                                115.7 458912.0 5438786.205 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </core:lod2Solid>
              <con:isStructuralElement>true</con:isStructuralElement>
              <con:filling>
                <con:Window
                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.xScpPtAxLzHxzuP1YU86">
                  <gml:name>17 - Ground Floor Window01 East</gml:name>
                  <core:lod2Solid>
                    <gml:Solid>
                      <gml:exterior>
                        <gml:Shell>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458912.0 5438788.205 115.7 458911.7
                                    5438788.205 115.7 458911.7 5438786.205 115.7 458912.0
                                    5438786.205 115.7 458912.0 5438788.205 115.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458912.0 5438788.205 114.5 458911.7
                                    5438788.205 114.5 458911.7 5438788.205 115.7 458912.0
                                    5438788.205 115.7 458912.0 5438788.205 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438788.205 114.5 458911.7
                                    5438786.205 114.5 458911.7 5438786.205 115.7 458911.7
                                    5438788.205 115.7 458911.7 5438788.205 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.xScpPtAxLzHxzuP1YU86_PG.Ts4Xm94yf5sdqEh6DGPh">
                              <gml:exterior>
                                <gml:LinearRing
                                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.xScpPtAxLzHxzuP1YU86_LR.VJX63X8ytoACnOWVhI5H">
                                  <gml:posList srsDimension="3">458912.0 5438786.205 114.5 458912.0
                                    5438788.205 114.5 458912.0 5438788.205 115.7 458912.0
                                    5438786.205 115.7 458912.0 5438786.205 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438786.205 114.5 458912.0
                                    5438786.205 114.5 458912.0 5438786.205 115.7 458911.7
                                    5438786.205 115.7 458911.7 5438786.205 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438788.205 114.5 458912.0
                                    5438788.205 114.5 458912.0 5438786.205 114.5 458911.7
                                    5438786.205 114.5 458911.7 5438788.205 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                        </gml:Shell>
                      </gml:exterior>
                    </gml:Solid>
                  </core:lod2Solid>
                </con:Window>
              </con:filling>
              <con:filling>
                <con:Window
                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.kYrOrTm2uRtVnUR7dmUA">
                  <gml:name>19 - Ground Floor Window02 East</gml:name>
                  <core:lod2Solid>
                    <gml:Solid>
                      <gml:exterior>
                        <gml:Shell>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438793.502394 114.5
                                    458911.7 5438791.502394 114.5 458911.7 5438791.502394 115.7
                                    458911.7 5438793.502394 115.7 458911.7 5438793.502394
                                    114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458912.0 5438791.502394 114.5
                                    458911.7 5438791.502394 114.5 458911.7 5438793.502394 114.5
                                    458912.0 5438793.502394 114.5 458912.0 5438791.502394
                                    114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458912.0 5438793.502394 115.7
                                    458911.7 5438793.502394 115.7 458911.7 5438791.502394 115.7
                                    458912.0 5438791.502394 115.7 458912.0 5438793.502394
                                    115.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.kYrOrTm2uRtVnUR7dmUA_PG.2DZe7GT9Oiq63oxvYXH8">
                              <gml:exterior>
                                <gml:LinearRing
                                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.kYrOrTm2uRtVnUR7dmUA_LR.wjN5SupLrHejqQJu7DZ5">
                                  <gml:posList srsDimension="3">458912.0 5438791.502394 114.5
                                    458912.0 5438793.502394 114.5 458912.0 5438793.502394 115.7
                                    458912.0 5438791.502394 115.7 458912.0 5438791.502394
                                    114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438791.502394 114.5
                                    458912.0 5438791.502394 114.5 458912.0 5438791.502394 115.7
                                    458911.7 5438791.502394 115.7 458911.7 5438791.502394
                                    114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458912.0 5438793.502394 114.5
                                    458911.7 5438793.502394 114.5 458911.7 5438793.502394 115.7
                                    458912.0 5438793.502394 115.7 458912.0 5438793.502394
                                    114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                        </gml:Shell>
                      </gml:exterior>
                    </gml:Solid>
                  </core:lod2Solid>
                </con:Window>
              </con:filling>
              <bldg:class>Wall</bldg:class>
            </bldg:BuildingConstructiveElement>
          </bldg:buildingConstructiveElement>
          <bldg:buildingConstructiveElement>
            <bldg:BuildingConstructiveElement
              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B">
              <gml:name>04 - Ground Floor Wall South</gml:name>
              <core:lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.4gTm9Bn7UbEWgQC8bSjy">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438785.3 113.7 458904.995
                                5438785.3 113.7 458904.995 5438785.0 113.7 458900.0 5438785.0 113.7
                                458900.3 5438785.3 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.b3mjhZdQleXFPUFsFOtI">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438785.3 113.7 458911.7
                                5438785.3 116.4 458912.0 5438785.0 116.4 458912.0 5438785.0 113.7
                                458911.7 5438785.3 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.hw3f6eDbUYzCmHsHFes4">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438785.3 116.4 458900.3
                                5438785.3 116.4 458900.0 5438785.0 116.4 458912.0 5438785.0 116.4
                                458911.7 5438785.3 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.LyKVhIOZtjzTySwNZTdg">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438785.0 113.7 458900.0
                                5438785.0 116.4 458900.3 5438785.3 116.4 458900.3 5438785.3 113.7
                                458900.0 5438785.0 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.0wA1hgHax9ZFpRFs70nr">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458904.995 5438785.3 113.7 458900.3
                                5438785.3 113.7 458900.3 5438785.3 116.4 458911.7 5438785.3 116.4
                                458911.7 5438785.3 113.7 458907.005 5438785.3 113.7 458907.005
                                5438785.3 116.075 458904.995 5438785.3 116.075 458904.995 5438785.3
                                113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                          <gml:interior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458901.79 5438785.3 115.7 458901.79
                                5438785.3 114.5 458903.79 5438785.3 114.5 458903.79 5438785.3 115.7
                                458901.79 5438785.3 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                          <gml:interior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458908.21 5438785.3 114.5 458910.21
                                5438785.3 114.5 458910.21 5438785.3 115.7 458908.21 5438785.3 115.7
                                458908.21 5438785.3 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.Ak1NLFqBgU5p93bMXwFH">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_LR.ZdDKAMpD2ZrKtevMUejU">
                              <gml:posList srsDimension="3">458900.0 5438785.0 113.7 458904.995
                                5438785.0 113.7 458904.995 5438785.0 116.075 458907.005 5438785.0
                                116.075 458907.005 5438785.0 113.7 458912.0 5438785.0 113.7 458912.0
                                5438785.0 116.4 458900.0 5438785.0 116.4 458900.0 5438785.0
                                113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                          <gml:interior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_LR.Bwq4RdOfRlTfgYvYKJ5B">
                              <gml:posList srsDimension="3">458901.79 5438785.0 114.5 458901.79
                                5438785.0 115.7 458903.79 5438785.0 115.7 458903.79 5438785.0 114.5
                                458901.79 5438785.0 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                          <gml:interior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_LR.hKG6EV1RLY9KdvhmzAEm">
                              <gml:posList srsDimension="3">458910.21 5438785.0 114.5 458908.21
                                5438785.0 114.5 458908.21 5438785.0 115.7 458910.21 5438785.0 115.7
                                458910.21 5438785.0 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.ZZnKeSo7EXJSy2gZCycZ">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458901.79 5438785.0 115.7 458901.79
                                5438785.0 114.5 458901.79 5438785.3 114.5 458901.79 5438785.3 115.7
                                458901.79 5438785.0 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.Kqka9dTOu58LJgLRf6oy">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458901.79 5438785.0 114.5 458903.79
                                5438785.0 114.5 458903.79 5438785.3 114.5 458901.79 5438785.3 114.5
                                458901.79 5438785.0 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.iCnyy2BdLJAogLSs2i51">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.79 5438785.0 114.5 458903.79
                                5438785.0 115.7 458903.79 5438785.3 115.7 458903.79 5438785.3 114.5
                                458903.79 5438785.0 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.1jD7aTdoiCN3mQEEU42p">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.79 5438785.0 115.7 458901.79
                                5438785.0 115.7 458901.79 5438785.3 115.7 458903.79 5438785.3 115.7
                                458903.79 5438785.0 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.MX4Zm8jk3QUlybqISaBT">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.005 5438785.0 113.7 458907.005
                                5438785.0 116.075 458907.005 5438785.3 116.075 458907.005 5438785.3
                                113.7 458907.005 5438785.0 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.5x2UcEXiuHs9EvbsMsVN">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.005 5438785.0 116.075 458904.995
                                5438785.0 116.075 458904.995 5438785.3 116.075 458907.005 5438785.3
                                116.075 458907.005 5438785.0 116.075</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.TEySNz7HuCioG969UenF">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458904.995 5438785.0 116.075 458904.995
                                5438785.0 113.7 458904.995 5438785.3 113.7 458904.995 5438785.3
                                116.075 458904.995 5438785.0 116.075</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.YG5U5xi5KTUBxmf1iulN">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.005 5438785.0 113.7 458907.005
                                5438785.3 113.7 458911.7 5438785.3 113.7 458912.0 5438785.0 113.7
                                458907.005 5438785.0 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.bFZVcr6XLcXsJJwtRSSA">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458908.21 5438785.0 114.5 458910.21
                                5438785.0 114.5 458910.21 5438785.3 114.5 458908.21 5438785.3 114.5
                                458908.21 5438785.0 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.u1Xnrdz79ayx2kQ1pkpt">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458910.21 5438785.0 114.5 458910.21
                                5438785.0 115.7 458910.21 5438785.3 115.7 458910.21 5438785.3 114.5
                                458910.21 5438785.0 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.nBlDAapwzX2tqPLlwVbM">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458910.21 5438785.0 115.7 458908.21
                                5438785.0 115.7 458908.21 5438785.3 115.7 458910.21 5438785.3 115.7
                                458910.21 5438785.0 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.mxHNopzAdsGpwWldh3jf">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458908.21 5438785.0 115.7 458908.21
                                5438785.0 114.5 458908.21 5438785.3 114.5 458908.21 5438785.3 115.7
                                458908.21 5438785.0 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </core:lod2Solid>
              <con:isStructuralElement>true</con:isStructuralElement>
              <con:filling>
                <con:Window
                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.9aFq0L7vXwXHZHTBaShi">
                  <gml:name>14 - Ground Floor Window01 South</gml:name>
                  <core:lod2Solid>
                    <gml:Solid>
                      <gml:exterior>
                        <gml:Shell>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.9aFq0L7vXwXHZHTBaShi_PG.5zDET0PYEarac0QrwsrW">
                              <gml:exterior>
                                <gml:LinearRing
                                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.9aFq0L7vXwXHZHTBaShi_LR.p0evYWdChScHiKesrLSv">
                                  <gml:posList srsDimension="3">458901.79 5438785.0 114.5 458903.79
                                    5438785.0 114.5 458903.79 5438785.0 115.7 458901.79 5438785.0
                                    115.7 458901.79 5438785.0 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458903.79 5438785.3 114.5 458901.79
                                    5438785.3 114.5 458901.79 5438785.3 115.7 458903.79 5438785.3
                                    115.7 458903.79 5438785.3 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458903.79 5438785.3 114.5 458903.79
                                    5438785.0 114.5 458901.79 5438785.0 114.5 458901.79 5438785.3
                                    114.5 458903.79 5438785.3 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458903.79 5438785.0 115.7 458903.79
                                    5438785.3 115.7 458901.79 5438785.3 115.7 458901.79 5438785.0
                                    115.7 458903.79 5438785.0 115.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458903.79 5438785.0 114.5 458903.79
                                    5438785.3 114.5 458903.79 5438785.3 115.7 458903.79 5438785.0
                                    115.7 458903.79 5438785.0 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458901.79 5438785.3 114.5 458901.79
                                    5438785.0 114.5 458901.79 5438785.0 115.7 458901.79 5438785.3
                                    115.7 458901.79 5438785.3 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                        </gml:Shell>
                      </gml:exterior>
                    </gml:Solid>
                  </core:lod2Solid>
                </con:Window>
              </con:filling>
              <con:filling>
                <con:Window
                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.Wihqw5MOkP7pIbGLXREi">
                  <gml:name>16 - Ground Floor Window02 South</gml:name>
                  <core:lod2Solid>
                    <gml:Solid>
                      <gml:exterior>
                        <gml:Shell>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.Wihqw5MOkP7pIbGLXREi_PG.kAv2fdFy0RBKKQ63mOXW">
                              <gml:exterior>
                                <gml:LinearRing
                                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.Wihqw5MOkP7pIbGLXREi_LR.0OimShpXKYJ3dvJFZjVR">
                                  <gml:posList srsDimension="3">458908.21 5438785.0 114.5 458910.21
                                    5438785.0 114.5 458910.21 5438785.0 115.7 458908.21 5438785.0
                                    115.7 458908.21 5438785.0 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458910.21 5438785.0 115.7 458910.21
                                    5438785.3 115.7 458908.21 5438785.3 115.7 458908.21 5438785.0
                                    115.7 458910.21 5438785.0 115.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458910.21 5438785.0 114.5 458910.21
                                    5438785.3 114.5 458910.21 5438785.3 115.7 458910.21 5438785.0
                                    115.7 458910.21 5438785.0 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458908.21 5438785.0 114.5 458908.21
                                    5438785.3 114.5 458910.21 5438785.3 114.5 458910.21 5438785.0
                                    114.5 458908.21 5438785.0 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458910.21 5438785.3 114.5 458908.21
                                    5438785.3 114.5 458908.21 5438785.3 115.7 458910.21 5438785.3
                                    115.7 458910.21 5438785.3 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458908.21 5438785.3 114.5 458908.21
                                    5438785.0 114.5 458908.21 5438785.0 115.7 458908.21 5438785.3
                                    115.7 458908.21 5438785.3 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                        </gml:Shell>
                      </gml:exterior>
                    </gml:Solid>
                  </core:lod2Solid>
                </con:Window>
              </con:filling>
              <con:filling>
                <con:Door
                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.jalS9iFDeTazxLHKmvaT">
                  <gml:name>13 - Ground Floor Door01 South</gml:name>
                  <core:lod2Solid>
                    <gml:Solid>
                      <gml:exterior>
                        <gml:Shell>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458907.005 5438785.3 113.7
                                    458904.995 5438785.3 113.7 458904.995 5438785.3 116.075
                                    458907.005 5438785.3 116.075 458907.005 5438785.3
                                    113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458907.005 5438785.0 116.075
                                    458907.005 5438785.3 116.075 458904.995 5438785.3 116.075
                                    458904.995 5438785.0 116.075 458907.005 5438785.0
                                    116.075</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458904.995 5438785.0 113.7
                                    458904.995 5438785.3 113.7 458907.005 5438785.3 113.7 458907.005
                                    5438785.0 113.7 458904.995 5438785.0 113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.jalS9iFDeTazxLHKmvaT_PG.2Y9MQFrdNWo9l0wVSvOe">
                              <gml:exterior>
                                <gml:LinearRing
                                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.jalS9iFDeTazxLHKmvaT_LR.4oj9q66rJOIpS7IyvZh4">
                                  <gml:posList srsDimension="3">458904.995 5438785.0 113.7
                                    458907.005 5438785.0 113.7 458907.005 5438785.0 116.075
                                    458904.995 5438785.0 116.075 458904.995 5438785.0
                                    113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458907.005 5438785.0 113.7
                                    458907.005 5438785.3 113.7 458907.005 5438785.3 116.075
                                    458907.005 5438785.0 116.075 458907.005 5438785.0
                                    113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458904.995 5438785.3 113.7
                                    458904.995 5438785.0 113.7 458904.995 5438785.0 116.075
                                    458904.995 5438785.3 116.075 458904.995 5438785.3
                                    113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                        </gml:Shell>
                      </gml:exterior>
                    </gml:Solid>
                  </core:lod2Solid>
                </con:Door>
              </con:filling>
              <bldg:class>Wall</bldg:class>
            </bldg:BuildingConstructiveElement>
          </bldg:buildingConstructiveElement>
          <bldg:buildingConstructiveElement>
            <bldg:BuildingConstructiveElement
              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br">
              <gml:name>05 - Ground Floor Wall West</gml:name>
              <core:lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.MXGACnPExMsY4UiCGrB8">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438794.7 113.7 458900.3
                                5438790.505 113.7 458900.0 5438790.505 113.7 458900.0 5438795.0
                                113.7 458900.3 5438794.7 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.UJWd7iJ2rz9gw0Qaciao">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438785.0 113.7 458900.3
                                5438785.3 113.7 458900.3 5438785.3 116.4 458900.0 5438785.0 116.4
                                458900.0 5438785.0 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.aqE6OEqSUsgw6xdVacvi">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438785.3 116.4 458900.3
                                5438794.7 116.4 458900.0 5438795.0 116.4 458900.0 5438785.0 116.4
                                458900.3 5438785.3 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.85JPhnkJXV9VCUEij5l1">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438795.0 113.7 458900.0
                                5438795.0 116.4 458900.3 5438794.7 116.4 458900.3 5438794.7 113.7
                                458900.0 5438795.0 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.MnianrJYS1uOj6nfGUh2">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438785.3 116.4 458900.3
                                5438785.3 113.7 458900.3 5438789.495 113.7 458900.3 5438789.495
                                115.71 458900.3 5438790.505 115.71 458900.3 5438790.505 113.7
                                458900.3 5438794.7 113.7 458900.3 5438794.7 116.4 458900.3 5438785.3
                                116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                          <gml:interior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438793.495 114.5 458900.3
                                5438791.495 114.5 458900.3 5438791.495 115.7 458900.3 5438793.495
                                115.7 458900.3 5438793.495 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                          <gml:interior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438788.205 114.5 458900.3
                                5438786.205 114.5 458900.3 5438786.205 115.7 458900.3 5438788.205
                                115.7 458900.3 5438788.205 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.pT57K3pbUX6MaTHCDERp">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_LR.JGT7zuqwhdECH8z2rvYG">
                              <gml:posList srsDimension="3">458900.0 5438795.0 113.7 458900.0
                                5438790.505 113.7 458900.0 5438790.505 115.71 458900.0 5438789.495
                                115.71 458900.0 5438789.495 113.7 458900.0 5438785.0 113.7 458900.0
                                5438785.0 116.4 458900.0 5438795.0 116.4 458900.0 5438795.0
                                113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                          <gml:interior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_LR.cjhu9mKqlxqYDRjuXqYj">
                              <gml:posList srsDimension="3">458900.0 5438791.495 114.5 458900.0
                                5438793.495 114.5 458900.0 5438793.495 115.7 458900.0 5438791.495
                                115.7 458900.0 5438791.495 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                          <gml:interior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_LR.Y2HHH04DDGLJZx5evjWF">
                              <gml:posList srsDimension="3">458900.0 5438786.205 114.5 458900.0
                                5438788.205 114.5 458900.0 5438788.205 115.7 458900.0 5438786.205
                                115.7 458900.0 5438786.205 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.8Psj4NMvO34m3cvY6kHy">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438793.495 114.5 458900.0
                                5438791.495 114.5 458900.3 5438791.495 114.5 458900.3 5438793.495
                                114.5 458900.0 5438793.495 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.p9iCOl21RCJtgwdDHv3H">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438791.495 114.5 458900.0
                                5438791.495 115.7 458900.3 5438791.495 115.7 458900.3 5438791.495
                                114.5 458900.0 5438791.495 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.kQNdgKDffLSyMXVlMMNK">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438791.495 115.7 458900.0
                                5438793.495 115.7 458900.3 5438793.495 115.7 458900.3 5438791.495
                                115.7 458900.0 5438791.495 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.UcVah209j0Ktz9lwhFgf">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438793.495 115.7 458900.0
                                5438793.495 114.5 458900.3 5438793.495 114.5 458900.3 5438793.495
                                115.7 458900.0 5438793.495 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.0sFhg9grcQeaAez3S1Fd">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.495 113.7 458900.0
                                5438789.495 115.71 458900.3 5438789.495 115.71 458900.3 5438789.495
                                113.7 458900.0 5438789.495 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.TlgO9waAmYuRJoSvYD6C">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.495 115.71 458900.0
                                5438790.505 115.71 458900.3 5438790.505 115.71 458900.3 5438789.495
                                115.71 458900.0 5438789.495 115.71</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.1EZrBaUWdkbKInql9bZ3">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.505 115.71 458900.0
                                5438790.505 113.7 458900.3 5438790.505 113.7 458900.3 5438790.505
                                115.71 458900.0 5438790.505 115.71</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.1yUVEQ1OnJ45W9MwUdiz">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.495 113.7 458900.3
                                5438789.495 113.7 458900.3 5438785.3 113.7 458900.0 5438785.0 113.7
                                458900.0 5438789.495 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.0Vbkm1FF5ocf5wsl8ROm">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438788.205 114.5 458900.0
                                5438786.205 114.5 458900.3 5438786.205 114.5 458900.3 5438788.205
                                114.5 458900.0 5438788.205 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.Pc79XMOMb9epJn2eIztW">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438786.205 114.5 458900.0
                                5438786.205 115.7 458900.3 5438786.205 115.7 458900.3 5438786.205
                                114.5 458900.0 5438786.205 114.5</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.aSsju6BwCWKIfjvQ6NOr">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438786.205 115.7 458900.0
                                5438788.205 115.7 458900.3 5438788.205 115.7 458900.3 5438786.205
                                115.7 458900.0 5438786.205 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.X1v589eDY3eWLIZGaV2f">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438788.205 115.7 458900.0
                                5438788.205 114.5 458900.3 5438788.205 114.5 458900.3 5438788.205
                                115.7 458900.0 5438788.205 115.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </core:lod2Solid>
              <con:isStructuralElement>true</con:isStructuralElement>
              <con:filling>
                <con:Window
                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.Rw7n0cJgxfN3IozXPOgX">
                  <gml:name>12 - Ground Floor Window01 West</gml:name>
                  <core:lod2Solid>
                    <gml:Solid>
                      <gml:exterior>
                        <gml:Shell>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438791.495 114.5 458900.3
                                    5438793.495 114.5 458900.3 5438793.495 115.7 458900.3
                                    5438791.495 115.7 458900.3 5438791.495 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.Rw7n0cJgxfN3IozXPOgX_PG.1LuWrQuylhqL07NV4rfH">
                              <gml:exterior>
                                <gml:LinearRing
                                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.Rw7n0cJgxfN3IozXPOgX_LR.J5NSMaSOrDg8DhLvW3q5">
                                  <gml:posList srsDimension="3">458900.0 5438791.495 114.5 458900.0
                                    5438791.495 115.7 458900.0 5438793.495 115.7 458900.0
                                    5438793.495 114.5 458900.0 5438791.495 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438793.495 114.5 458900.0
                                    5438793.495 114.5 458900.0 5438793.495 115.7 458900.3
                                    5438793.495 115.7 458900.3 5438793.495 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.0 5438791.495 115.7 458900.3
                                    5438791.495 115.7 458900.3 5438793.495 115.7 458900.0
                                    5438793.495 115.7 458900.0 5438791.495 115.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438791.495 114.5 458900.0
                                    5438791.495 114.5 458900.0 5438793.495 114.5 458900.3
                                    5438793.495 114.5 458900.3 5438791.495 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.0 5438791.495 114.5 458900.3
                                    5438791.495 114.5 458900.3 5438791.495 115.7 458900.0
                                    5438791.495 115.7 458900.0 5438791.495 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                        </gml:Shell>
                      </gml:exterior>
                    </gml:Solid>
                  </core:lod2Solid>
                </con:Window>
              </con:filling>
              <con:filling>
                <con:Window
                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.OZzJ0PyiUVwgxGghWLkd">
                  <gml:name>20 - Ground Floor Window02 West</gml:name>
                  <core:lod2Solid>
                    <gml:Solid>
                      <gml:exterior>
                        <gml:Shell>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.OZzJ0PyiUVwgxGghWLkd_PG.MeDGx6kKAKC0FGVtIi5b">
                              <gml:exterior>
                                <gml:LinearRing
                                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.OZzJ0PyiUVwgxGghWLkd_LR.oE2fLm99BAZXCqLfR1Hu">
                                  <gml:posList srsDimension="3">458900.0 5438786.205 114.5 458900.0
                                    5438786.205 115.7 458900.0 5438788.205 115.7 458900.0
                                    5438788.205 114.5 458900.0 5438786.205 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438786.205 114.5 458900.3
                                    5438788.205 114.5 458900.3 5438788.205 115.7 458900.3
                                    5438786.205 115.7 458900.3 5438786.205 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.0 5438786.205 115.7 458900.3
                                    5438786.205 115.7 458900.3 5438788.205 115.7 458900.0
                                    5438788.205 115.7 458900.0 5438786.205 115.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.0 5438786.205 114.5 458900.3
                                    5438786.205 114.5 458900.3 5438786.205 115.7 458900.0
                                    5438786.205 115.7 458900.0 5438786.205 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438788.205 114.5 458900.0
                                    5438788.205 114.5 458900.0 5438788.205 115.7 458900.3
                                    5438788.205 115.7 458900.3 5438788.205 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.0 5438788.205 114.5 458900.3
                                    5438788.205 114.5 458900.3 5438786.205 114.5 458900.0
                                    5438786.205 114.5 458900.0 5438788.205 114.5</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                        </gml:Shell>
                      </gml:exterior>
                    </gml:Solid>
                  </core:lod2Solid>
                </con:Window>
              </con:filling>
              <con:filling>
                <con:Door
                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.vTExwGEkNkFYB3tAnTrl">
                  <gml:name>22 - Ground Floor Door01 West</gml:name>
                  <core:lod2Solid>
                    <gml:Solid>
                      <gml:exterior>
                        <gml:Shell>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.505 113.7 458900.0
                                    5438790.505 113.7 458900.0 5438790.505 115.71 458900.3
                                    5438790.505 115.71 458900.3 5438790.505 113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.0 5438789.495 115.71 458900.3
                                    5438789.495 115.71 458900.3 5438790.505 115.71 458900.0
                                    5438790.505 115.71 458900.0 5438789.495 115.71</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.495 113.7 458900.3
                                    5438790.505 113.7 458900.3 5438790.505 115.71 458900.3
                                    5438789.495 115.71 458900.3 5438789.495 113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.0 5438790.505 113.7 458900.3
                                    5438790.505 113.7 458900.3 5438789.495 113.7 458900.0
                                    5438789.495 113.7 458900.0 5438790.505 113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.vTExwGEkNkFYB3tAnTrl_PG.OiuqA95bz0nXwSZHl3Dj">
                              <gml:exterior>
                                <gml:LinearRing
                                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.vTExwGEkNkFYB3tAnTrl_LR.CefnAcQCtIPEZDGHunE4">
                                  <gml:posList srsDimension="3">458900.0 5438790.505 113.7 458900.0
                                    5438789.495 113.7 458900.0 5438789.495 115.71 458900.0
                                    5438790.505 115.71 458900.0 5438790.505 113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.0 5438789.495 113.7 458900.3
                                    5438789.495 113.7 458900.3 5438789.495 115.71 458900.0
                                    5438789.495 115.71 458900.0 5438789.495 113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                        </gml:Shell>
                      </gml:exterior>
                    </gml:Solid>
                  </core:lod2Solid>
                </con:Door>
              </con:filling>
              <bldg:class>Wall</bldg:class>
            </bldg:BuildingConstructiveElement>
          </bldg:buildingConstructiveElement>
          <bldg:buildingConstructiveElement>
            <bldg:BuildingConstructiveElement
              gml:id="_Construstruction-Inner-Walls-Openings_BD.qRkdlaRa8N0CQtbdEIFv">
              <gml:name>06 - Ground Floor Wall Interior 01</gml:name>
              <core:lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.qRkdlaRa8N0CQtbdEIFv_PG.d8kVAyrlEU9CrfA8A2gW">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438789.25 116.2 458903.8
                                5438789.25 116.2 458903.8 5438789.25 113.7 458900.3 5438789.25 113.7
                                458900.3 5438789.25 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.qRkdlaRa8N0CQtbdEIFv_PG.uJsLK8i5SurJiExGFyi3">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.8 5438789.01 113.7 458900.3
                                5438789.01 113.7 458900.3 5438789.25 113.7 458903.8 5438789.25 113.7
                                458903.8 5438789.01 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.qRkdlaRa8N0CQtbdEIFv_PG.FCQY9L7oBdnfiY6rV26u">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438789.01 113.7 458900.3
                                5438789.01 116.2 458900.3 5438789.25 116.2 458900.3 5438789.25 113.7
                                458900.3 5438789.01 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.qRkdlaRa8N0CQtbdEIFv_PG.6kA59FxHoahxQqrUEIte">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.8 5438789.01 116.2 458900.3
                                5438789.01 116.2 458900.3 5438789.01 113.7 458903.8 5438789.01 113.7
                                458903.8 5438789.01 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.qRkdlaRa8N0CQtbdEIFv_PG.XnNFobF5UIP6j0uH8aj5">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.8 5438789.01 116.2 458903.8
                                5438789.25 116.2 458900.3 5438789.25 116.2 458900.3 5438789.01 116.2
                                458903.8 5438789.01 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.qRkdlaRa8N0CQtbdEIFv_PG.dy7w8BKNhuDhLWCtEvMD">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.8 5438789.25 116.2 458903.8
                                5438789.01 116.2 458903.8 5438789.01 113.7 458903.8 5438789.25 113.7
                                458903.8 5438789.25 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </core:lod2Solid>
              <con:isStructuralElement>true</con:isStructuralElement>
              <bldg:class>Wall</bldg:class>
            </bldg:BuildingConstructiveElement>
          </bldg:buildingConstructiveElement>
          <bldg:buildingConstructiveElement>
            <bldg:BuildingConstructiveElement
              gml:id="_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd">
              <gml:name>07 - Ground Floor Wall Interior 02</gml:name>
              <core:lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.tevoh8uvM5ObHej38qSR">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438790.99 113.7 458900.3
                                5438790.99 116.2 458907.41 5438790.99 116.2 458907.41 5438790.99
                                113.7 458906.1025 5438790.99 113.7 458906.1025 5438790.99 115.71
                                458905.2175 5438790.99 115.71 458905.2175 5438790.99 113.7
                                458902.4925 5438790.99 113.7 458902.4925 5438790.99 115.71
                                458901.6075 5438790.99 115.71 458901.6075 5438790.99 113.7 458900.3
                                5438790.99 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.ivw57JFf2lTDeLw4Ibtn">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458901.6075 5438790.75 113.7 458900.3
                                5438790.75 113.7 458900.3 5438790.99 113.7 458901.6075 5438790.99
                                113.7 458901.6075 5438790.75 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.PEFnRCNDFqbEaU7t0w7Z">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458901.6075 5438790.99 115.71
                                458901.6075 5438790.75 115.71 458901.6075 5438790.75 113.7
                                458901.6075 5438790.99 113.7 458901.6075 5438790.99
                                115.71</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.4Kz1yToBEi5liZmlaZh5">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458902.4925 5438790.99 115.71
                                458902.4925 5438790.75 115.71 458901.6075 5438790.75 115.71
                                458901.6075 5438790.99 115.71 458902.4925 5438790.99
                                115.71</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.Dsw1ReWByNvMnfqrQVa4">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458902.4925 5438790.99 113.7 458902.4925
                                5438790.75 113.7 458902.4925 5438790.75 115.71 458902.4925
                                5438790.99 115.71 458902.4925 5438790.99 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.EDfoUPuFxA56P18CIw6h">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458905.2175 5438790.75 113.7 458902.4925
                                5438790.75 113.7 458902.4925 5438790.99 113.7 458905.2175 5438790.99
                                113.7 458905.2175 5438790.75 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.gHBb4dieFnO2YLCkbCXW">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458905.2175 5438790.99 115.71
                                458905.2175 5438790.75 115.71 458905.2175 5438790.75 113.7
                                458905.2175 5438790.99 113.7 458905.2175 5438790.99
                                115.71</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.C4amUICXdGbBS8306cSz">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458906.1025 5438790.99 115.71
                                458906.1025 5438790.75 115.71 458905.2175 5438790.75 115.71
                                458905.2175 5438790.99 115.71 458906.1025 5438790.99
                                115.71</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.8VNFSjoGbq08vqjB0gG4">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458906.1025 5438790.99 113.7 458906.1025
                                5438790.75 113.7 458906.1025 5438790.75 115.71 458906.1025
                                5438790.99 115.71 458906.1025 5438790.99 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.TyPnnB5IO8HVuhbnoC9q">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.41 5438790.75 113.7 458906.1025
                                5438790.75 113.7 458906.1025 5438790.99 113.7 458907.41 5438790.99
                                113.7 458907.41 5438790.75 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.0vivLw0vUbUszB4tBrKk">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.41 5438790.75 113.7 458907.41
                                5438790.99 113.7 458907.41 5438790.99 116.2 458907.41 5438790.75
                                116.2 458907.41 5438790.75 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.AoqmwbSIvGPHY36XjJzi">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438790.75 116.2 458907.41
                                5438790.75 116.2 458907.41 5438790.99 116.2 458900.3 5438790.99
                                116.2 458900.3 5438790.75 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.2kp4YIe3H41GTYqmqzeF">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438790.75 113.7 458900.3
                                5438790.75 116.2 458900.3 5438790.99 116.2 458900.3 5438790.99 113.7
                                458900.3 5438790.75 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.9A5t86IpOPzmFEZBLaJz">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.41 5438790.75 113.7 458907.41
                                5438790.75 116.2 458900.3 5438790.75 116.2 458900.3 5438790.75 113.7
                                458901.6075 5438790.75 113.7 458901.6075 5438790.75 115.71
                                458902.4925 5438790.75 115.71 458902.4925 5438790.75 113.7
                                458905.2175 5438790.75 113.7 458905.2175 5438790.75 115.71
                                458906.1025 5438790.75 115.71 458906.1025 5438790.75 113.7 458907.41
                                5438790.75 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </core:lod2Solid>
              <con:isStructuralElement>false</con:isStructuralElement>
              <con:filling>
                <con:Door gml:id="_Construstruction-Inner-Walls-Openings_BD.ndMdKaHqHsTNYxoA22I4">
                  <gml:name>07-1 - Ground Floor Door Interior 01</gml:name>
                  <core:lod2Solid>
                    <gml:Solid>
                      <gml:exterior>
                        <gml:Shell>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_Construstruction-Inner-Walls-Openings_BD.ndMdKaHqHsTNYxoA22I4_PG.Xa9GyqpsPzN24MDzHbTn">
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458901.6075 5438790.99 113.7
                                    458902.4925 5438790.99 113.7 458902.4925 5438790.75 113.7
                                    458901.6075 5438790.75 113.7 458901.6075 5438790.99
                                    113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_Construstruction-Inner-Walls-Openings_BD.ndMdKaHqHsTNYxoA22I4_PG.X6blngoQWbijGXoskrmf">
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458902.4925 5438790.99 115.71
                                    458901.6075 5438790.99 115.71 458901.6075 5438790.75 115.71
                                    458902.4925 5438790.75 115.71 458902.4925 5438790.99
                                    115.71</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_Construstruction-Inner-Walls-Openings_BD.ndMdKaHqHsTNYxoA22I4_PG.vl76leAIUtpKkt3zW0hT">
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458902.4925 5438790.99 113.7
                                    458901.6075 5438790.99 113.7 458901.6075 5438790.99 115.71
                                    458902.4925 5438790.99 115.71 458902.4925 5438790.99
                                    113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_Construstruction-Inner-Walls-Openings_BD.ndMdKaHqHsTNYxoA22I4_PG.m5aniKKE8QA4x8MKMX7L">
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458902.4925 5438790.99 113.7
                                    458902.4925 5438790.99 115.71 458902.4925 5438790.75 115.71
                                    458902.4925 5438790.75 113.7 458902.4925 5438790.99
                                    113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_Construstruction-Inner-Walls-Openings_BD.ndMdKaHqHsTNYxoA22I4_PG.NIZLSIFLwMD5JtEalVWd">
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458901.6075 5438790.99 115.71
                                    458901.6075 5438790.99 113.7 458901.6075 5438790.75 113.7
                                    458901.6075 5438790.75 115.71 458901.6075 5438790.99
                                    115.71</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_Construstruction-Inner-Walls-Openings_BD.ndMdKaHqHsTNYxoA22I4_PG.0k5Xo1Cshx34V88a6RTR">
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458901.6075 5438790.75 113.7
                                    458902.4925 5438790.75 113.7 458902.4925 5438790.75 115.71
                                    458901.6075 5438790.75 115.71 458901.6075 5438790.75
                                    113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                        </gml:Shell>
                      </gml:exterior>
                    </gml:Solid>
                  </core:lod2Solid>
                  <con:class>IfcDoor</con:class>
                </con:Door>
              </con:filling>
              <con:filling>
                <con:Door gml:id="_Construstruction-Inner-Walls-Openings_BD.S4cjevrMiB08tLVcvpbt">
                  <gml:name>07-2 - Ground Floor Door Interior 02</gml:name>
                  <core:lod2Solid>
                    <gml:Solid>
                      <gml:exterior>
                        <gml:Shell>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_Construstruction-Inner-Walls-Openings_BD.S4cjevrMiB08tLVcvpbt_PG.qigoD3DkmcLetNdTV1jc">
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458906.1025 5438790.99 113.7
                                    458905.2175 5438790.99 113.7 458905.2175 5438790.99 115.71
                                    458906.1025 5438790.99 115.71 458906.1025 5438790.99
                                    113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_Construstruction-Inner-Walls-Openings_BD.S4cjevrMiB08tLVcvpbt_PG.JjGGVrHaxzjahKoY3UTU">
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458906.1025 5438790.99 115.71
                                    458905.2175 5438790.99 115.71 458905.2175 5438790.75 115.71
                                    458906.1025 5438790.75 115.71 458906.1025 5438790.99
                                    115.71</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_Construstruction-Inner-Walls-Openings_BD.S4cjevrMiB08tLVcvpbt_PG.xjYYVWMc8hpf5UDFA7nQ">
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458905.2175 5438790.75 113.7
                                    458906.1025 5438790.75 113.7 458906.1025 5438790.75 115.71
                                    458905.2175 5438790.75 115.71 458905.2175 5438790.75
                                    113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_Construstruction-Inner-Walls-Openings_BD.S4cjevrMiB08tLVcvpbt_PG.miOcSXhUmXAyQxbRzaRq">
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458905.2175 5438790.99 113.7
                                    458906.1025 5438790.99 113.7 458906.1025 5438790.75 113.7
                                    458905.2175 5438790.75 113.7 458905.2175 5438790.99
                                    113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_Construstruction-Inner-Walls-Openings_BD.S4cjevrMiB08tLVcvpbt_PG.yUAhidnLEVKcjQv9a3K1">
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458906.1025 5438790.99 113.7
                                    458906.1025 5438790.99 115.71 458906.1025 5438790.75 115.71
                                    458906.1025 5438790.75 113.7 458906.1025 5438790.99
                                    113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_Construstruction-Inner-Walls-Openings_BD.S4cjevrMiB08tLVcvpbt_PG.CKT9RydeebnO38lN8YxL">
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458905.2175 5438790.99 115.71
                                    458905.2175 5438790.99 113.7 458905.2175 5438790.75 113.7
                                    458905.2175 5438790.75 115.71 458905.2175 5438790.99
                                    115.71</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                        </gml:Shell>
                      </gml:exterior>
                    </gml:Solid>
                  </core:lod2Solid>
                  <con:class>IfcDoor</con:class>
                </con:Door>
              </con:filling>
              <bldg:class>Wall</bldg:class>
            </bldg:BuildingConstructiveElement>
          </bldg:buildingConstructiveElement>
          <bldg:buildingConstructiveElement>
            <bldg:BuildingConstructiveElement
              gml:id="_Construstruction-Inner-Walls-Openings_BD.R1DJ5JpOrRkQXkwPmUBa">
              <gml:name>08 - Ground Floor Wall Interior 03</gml:name>
              <core:lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.R1DJ5JpOrRkQXkwPmUBa_PG.hxsvwtyAn5axgrUjw5WN">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438789.01 116.2 458907.41
                                5438789.01 116.2 458907.41 5438789.01 113.7 458911.7 5438789.01
                                113.7 458911.7 5438789.01 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.R1DJ5JpOrRkQXkwPmUBa_PG.oTZeCOYgqyCjdwhXqlqP">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438789.25 113.7 458911.7
                                5438789.01 113.7 458907.41 5438789.01 113.7 458907.65 5438789.25
                                113.7 458911.7 5438789.25 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.R1DJ5JpOrRkQXkwPmUBa_PG.5EpvkqWfeZT294U7KZaX">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.41 5438789.01 113.7 458907.41
                                5438789.01 116.2 458907.65 5438789.25 116.2 458907.65 5438789.25
                                113.7 458907.41 5438789.01 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon gml:id="UUID_8914e1c3-ea3a-4d49-9a04-14c6d3ef6ea3">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438789.25 116.2 458907.65
                                5438789.25 116.2 458907.41 5438789.01 116.2 458911.7 5438789.01
                                116.2 458911.7 5438789.25 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.R1DJ5JpOrRkQXkwPmUBa_PG.NJZouCBgRo0ocAOH7S2B">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438789.01 113.7 458911.7
                                5438789.25 113.7 458911.7 5438789.25 116.2 458911.7 5438789.01 116.2
                                458911.7 5438789.01 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.R1DJ5JpOrRkQXkwPmUBa_PG.fEegQAGXMwPfM29hj4Jp">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.65 5438789.25 116.2 458911.7
                                5438789.25 116.2 458911.7 5438789.25 113.7 458907.65 5438789.25
                                113.7 458907.65 5438789.25 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </core:lod2Solid>
              <con:isStructuralElement>true</con:isStructuralElement>
              <bldg:class>Wall</bldg:class>
            </bldg:BuildingConstructiveElement>
          </bldg:buildingConstructiveElement>
          <bldg:buildingConstructiveElement>
            <bldg:BuildingConstructiveElement
              gml:id="_Construstruction-Inner-Walls-Openings_BD.DQjKZ7HGEqZ7Z3ubUp0N">
              <gml:name>09 - Ground Floor Wall Interior 04</gml:name>
              <core:lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.DQjKZ7HGEqZ7Z3ubUp0N_PG.35Ew3lUPb7MKZrZjk1lq">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458904.04 5438794.7 116.2 458904.04
                                5438790.99 116.2 458904.04 5438790.99 113.7 458904.04 5438794.7
                                113.7 458904.04 5438794.7 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.DQjKZ7HGEqZ7Z3ubUp0N_PG.RhAkTStqrkUoYKWMY5ay">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.8 5438790.99 113.7 458903.8
                                5438794.7 113.7 458904.04 5438794.7 113.7 458904.04 5438790.99 113.7
                                458903.8 5438790.99 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.DQjKZ7HGEqZ7Z3ubUp0N_PG.W7a53czBjI5fGEOkxRhm">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.8 5438790.99 113.7 458904.04
                                5438790.99 113.7 458904.04 5438790.99 116.2 458903.8 5438790.99
                                116.2 458903.8 5438790.99 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.DQjKZ7HGEqZ7Z3ubUp0N_PG.aGfkflazY9Z022vmKreZ">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.8 5438794.7 116.2 458903.8
                                5438790.99 116.2 458904.04 5438790.99 116.2 458904.04 5438794.7
                                116.2 458903.8 5438794.7 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.DQjKZ7HGEqZ7Z3ubUp0N_PG.3t0rTpC2wit2gUeLZ3ua">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.8 5438794.7 113.7 458903.8
                                5438794.7 116.2 458904.04 5438794.7 116.2 458904.04 5438794.7 113.7
                                458903.8 5438794.7 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.DQjKZ7HGEqZ7Z3ubUp0N_PG.XCqVAzhRwVkldJT6lLSP">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.8 5438790.99 116.2 458903.8
                                5438794.7 116.2 458903.8 5438794.7 113.7 458903.8 5438790.99 113.7
                                458903.8 5438790.99 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </core:lod2Solid>
              <con:isStructuralElement>false</con:isStructuralElement>
              <bldg:class>Wall</bldg:class>
            </bldg:BuildingConstructiveElement>
          </bldg:buildingConstructiveElement>
          <bldg:buildingConstructiveElement>
            <bldg:BuildingConstructiveElement
              gml:id="_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0">
              <gml:name>10 - Ground Floor Wall Interior 05</gml:name>
              <core:lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.7B9cENkB33kDDJ3LwzGe">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.65 5438789.5575 113.7 458907.41
                                5438789.5575 113.7 458907.41 5438789.5575 115.71 458907.65
                                5438789.5575 115.71 458907.65 5438789.5575 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.ge6tBACJRyFV56CWHEzA">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.65 5438794.7 113.7 458907.65
                                5438794.7 116.2 458907.65 5438789.25 116.2 458907.65 5438789.25
                                113.7 458907.65 5438789.5575 113.7 458907.65 5438789.5575 115.71
                                458907.65 5438790.4425 115.71 458907.65 5438790.4425 113.7 458907.65
                                5438794.7 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.7aGP838SmLScKDpjVjvk">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.41 5438790.4425 113.7 458907.41
                                5438794.7 113.7 458907.65 5438794.7 113.7 458907.65 5438790.4425
                                113.7 458907.41 5438790.4425 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.5yZhBXvPX1yQmmawrZir">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.65 5438794.7 116.2 458907.41
                                5438794.7 116.2 458907.41 5438789.01 116.2 458907.65 5438789.25
                                116.2 458907.65 5438794.7 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.nrQ6ruhxHc4uf9SPzen7">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.65 5438789.25 113.7 458907.65
                                5438789.25 116.2 458907.41 5438789.01 116.2 458907.41 5438789.01
                                113.7 458907.65 5438789.25 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.8cTY19D4y3xawTYYl4av">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.41 5438789.01 113.7 458907.41
                                5438789.5575 113.7 458907.65 5438789.5575 113.7 458907.65 5438789.25
                                113.7 458907.41 5438789.01 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.x1aYJYAwBW3WPvfk1tHY">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.65 5438790.4425 115.71 458907.41
                                5438790.4425 115.71 458907.41 5438790.4425 113.7 458907.65
                                5438790.4425 113.7 458907.65 5438790.4425 115.71</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.1CGknnSuXNhCilZOKJ4t">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.65 5438789.5575 115.71 458907.41
                                5438789.5575 115.71 458907.41 5438790.4425 115.71 458907.65
                                5438790.4425 115.71 458907.65 5438789.5575 115.71</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.KLuDhHDCBMAxDavA6wtK">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.41 5438794.7 113.7 458907.41
                                5438794.7 116.2 458907.65 5438794.7 116.2 458907.65 5438794.7 113.7
                                458907.41 5438794.7 113.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.cAXauiJAb8w8JmB8JScQ">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.41 5438794.7 116.2 458907.41
                                5438794.7 113.7 458907.41 5438790.4425 113.7 458907.41 5438790.4425
                                115.71 458907.41 5438789.5575 115.71 458907.41 5438789.5575 113.7
                                458907.41 5438789.01 113.7 458907.41 5438789.01 116.2 458907.41
                                5438794.7 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </core:lod2Solid>
              <con:isStructuralElement>false</con:isStructuralElement>
              <con:filling>
                <con:Door gml:id="_Construstruction-Inner-Walls-Openings_BD.ZVLOAloklMK3sl7leFKU">
                  <gml:name>10-1 - Ground Floor Door Interior 01</gml:name>
                  <core:lod2Solid>
                    <gml:Solid>
                      <gml:exterior>
                        <gml:Shell>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_Construstruction-Inner-Walls-Openings_BD.ZVLOAloklMK3sl7leFKU_PG.Vf8fOK0ooOc2ASNntwTz">
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458907.41 5438790.4425 113.7
                                    458907.41 5438789.5575 113.7 458907.41 5438789.5575 115.71
                                    458907.41 5438790.4425 115.71 458907.41 5438790.4425
                                    113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_Construstruction-Inner-Walls-Openings_BD.ZVLOAloklMK3sl7leFKU_PG.Iz4ZBl4yTYEAiKyuQuGk">
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458907.41 5438790.4425 115.71
                                    458907.41 5438789.5575 115.71 458907.65 5438789.5575 115.71
                                    458907.65 5438790.4425 115.71 458907.41 5438790.4425
                                    115.71</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_Construstruction-Inner-Walls-Openings_BD.ZVLOAloklMK3sl7leFKU_PG.sHiD8NjLLWIvEideopmW">
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458907.41 5438789.5575 115.71
                                    458907.41 5438789.5575 113.7 458907.65 5438789.5575 113.7
                                    458907.65 5438789.5575 115.71 458907.41 5438789.5575
                                    115.71</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_Construstruction-Inner-Walls-Openings_BD.ZVLOAloklMK3sl7leFKU_PG.pN7xEGh1tE2QFhsB5NJ3">
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458907.41 5438789.5575 113.7
                                    458907.41 5438790.4425 113.7 458907.65 5438790.4425 113.7
                                    458907.65 5438789.5575 113.7 458907.41 5438789.5575
                                    113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_Construstruction-Inner-Walls-Openings_BD.ZVLOAloklMK3sl7leFKU_PG.xBPEJonLeNMyONoDn60v">
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458907.65 5438789.5575 113.7
                                    458907.65 5438790.4425 113.7 458907.65 5438790.4425 115.71
                                    458907.65 5438789.5575 115.71 458907.65 5438789.5575
                                    113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_Construstruction-Inner-Walls-Openings_BD.ZVLOAloklMK3sl7leFKU_PG.pthjYxD2taiINiLHE22G">
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458907.41 5438790.4425 113.7
                                    458907.41 5438790.4425 115.71 458907.65 5438790.4425 115.71
                                    458907.65 5438790.4425 113.7 458907.41 5438790.4425
                                    113.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                        </gml:Shell>
                      </gml:exterior>
                    </gml:Solid>
                  </core:lod2Solid>
                  <con:class>IfcDoor</con:class>
                </con:Door>
              </con:filling>
              <bldg:class>Wall</bldg:class>
            </bldg:BuildingConstructiveElement>
          </bldg:buildingConstructiveElement>
          <bldg:buildingConstructiveElement>
            <bldg:BuildingConstructiveElement
              gml:id="_Construstruction-Inner-Walls-no-Openings_BD.kJGTyM0ej3KRALTSvj2Y">
              <gml:name>11 - Beam - Ground Floor - Interior</gml:name>
              <core:lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.DoaCjMeE7wRjFY1VZlF3">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.8 5438789.03 115.96 458903.8
                                5438789.23 115.96 458907.41 5438789.23 115.96 458907.41 5438789.03
                                115.96 458903.8 5438789.03 115.96</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.wLHm56rDZnjOqHhmES66">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.8 5438789.03 116.2 458903.8
                                5438789.03 115.96 458907.41 5438789.03 115.96 458907.41 5438789.03
                                116.2 458903.8 5438789.03 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.DpINacYwpfduPx1yRDjS">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.8 5438789.23 115.96 458903.8
                                5438789.03 115.96 458903.8 5438789.03 116.2 458903.8 5438789.23
                                116.2 458903.8 5438789.23 115.96</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.HBYn9IMWyNmmyGkNStCs">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.8 5438789.23 116.2 458903.8
                                5438789.03 116.2 458907.41 5438789.03 116.2 458907.41 5438789.23
                                116.2 458903.8 5438789.23 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.z7d6kVNAoAERqCrq30mr">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458903.8 5438789.23 115.96 458903.8
                                5438789.23 116.2 458907.41 5438789.23 116.2 458907.41 5438789.23
                                115.96 458903.8 5438789.23 115.96</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.5yqkqjxgualuoLP6R7gV">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.41 5438789.03 115.96 458907.41
                                5438789.23 115.96 458907.41 5438789.23 116.2 458907.41 5438789.03
                                116.2 458907.41 5438789.03 115.96</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </core:lod2Solid>
              <con:isStructuralElement>true</con:isStructuralElement>
              <bldg:class>Beam</bldg:class>
            </bldg:BuildingConstructiveElement>
          </bldg:buildingConstructiveElement>
        </bldg:Storey>
      </bldg:buildingSubdivision>
      <bldg:buildingSubdivision>
        <bldg:Storey>
          <gml:name>Second Floor</gml:name>
          <bldg:class>non Entrance Floor</bldg:class>
          <bldg:buildingConstructiveElement>
            <bldg:BuildingConstructiveElement
              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr">
              <gml:name>06 - Second Floor Roof North</gml:name>
              <core:lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_PG.Iu5Q93HicOBRznKlBKqE">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_LR.QoAZ8VWB78kYm2QHCFI8">
                              <gml:posList srsDimension="3">458899.5 5438795.5 116.842265 458899.5
                                5438795.5 116.611325 458899.5 5438790.0 119.786751 458899.5
                                5438790.0 120.017691 458899.5 5438795.5 116.842265</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_PG.2DXeCrnYFTe4NBLbTIGC">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_LR.wh2wvw14vCxyRj2iUv7x">
                              <gml:posList srsDimension="3">458912.5 5438795.5 116.842265 458912.5
                                5438795.5 116.611325 458899.5 5438795.5 116.611325 458899.5
                                5438795.5 116.842265 458912.5 5438795.5 116.842265</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_PG.9FctWwzZPerF6BIy3sqj">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_LR.Q1wBVMNITizsmPow89Gt">
                              <gml:posList srsDimension="3">458912.5 5438790.0 120.017691 458912.5
                                5438790.0 119.786751 458912.5 5438795.5 116.611325 458912.5
                                5438795.5 116.842265 458912.5 5438790.0 120.017691</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_PG.oh6S5N4J9aSMQrA5Q4ia">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_LR.SFEv1iSdjHlJuIbGUoX3">
                              <gml:posList srsDimension="3">458899.5 5438790.0 120.017691 458899.5
                                5438790.0 119.786751 458912.5 5438790.0 119.786751 458912.5
                                5438790.0 120.017691 458899.5 5438790.0 120.017691</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_PG.HFO41EX8efenwmGi5Eft">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_LR.RWrpZWqwlNoeBXW90htk">
                              <gml:posList srsDimension="3">458912.5 5438795.5 116.611325 458912.5
                                5438790.0 119.786751 458899.5 5438790.0 119.786751 458899.5
                                5438795.5 116.611325 458912.5 5438795.5 116.611325</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_PG.Qaoo4itOZjJIW0peZkt5">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_LR.tzqFUfEx4Nk6eMlakzSH">
                              <gml:posList srsDimension="3">458912.5 5438790.0 120.017691 458912.5
                                5438795.5 116.842265 458899.5 5438795.5 116.842265 458899.5
                                5438790.0 120.017691 458912.5 5438790.0 120.017691</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </core:lod2Solid>
              <con:isStructuralElement>true</con:isStructuralElement>
              <bldg:class>Roof</bldg:class>
            </bldg:BuildingConstructiveElement>
          </bldg:buildingConstructiveElement>
          <bldg:buildingConstructiveElement>
            <bldg:BuildingConstructiveElement
              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh">
              <gml:name>07 - Second Floor Wall East</gml:name>
              <core:lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.9Pf9ymItQA6c2I2WvtV5">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438785.3 116.4 458911.7
                                5438794.7 116.4 458912.0 5438795.0 116.4 458912.0 5438785.0 116.4
                                458911.7 5438785.3 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.yuP7cbU7A3IxfCFGy97D">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438794.7 117.073205 458912.0
                                5438795.0 116.9 458912.0 5438795.0 116.4 458911.7 5438794.7 116.4
                                458911.7 5438794.7 117.073205</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.BpdaCGTkNdGGdyOQrqkl">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438785.0 116.4 458912.0
                                5438785.0 116.9 458911.7 5438785.3 117.073205 458911.7 5438785.3
                                116.4 458912.0 5438785.0 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.99Q5UITX3dQ5iiv8R5vZ">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.0 119.786751 458912.0
                                5438795.0 116.9 458911.7 5438794.7 117.073205 458911.7 5438790.0
                                119.786751 458912.0 5438790.0 119.786751</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.OaIh1pItuIcY4oibiKgA">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438790.0 119.786751 458911.7
                                5438785.3 117.073205 458912.0 5438785.0 116.9 458912.0 5438790.0
                                119.786751 458911.7 5438790.0 119.786751</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.otkas6NaobDYfzhMCJfV">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438794.7 117.073205 458911.7
                                5438794.7 116.4 458911.7 5438785.3 116.4 458911.7 5438785.3
                                117.073205 458911.7 5438790.0 119.786751 458911.7 5438794.7
                                117.073205</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                          <gml:interior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438790.0 118.2 458911.7
                                5438789.950991 118.197592 458911.7 5438789.902455 118.190393
                                458911.7 5438789.854858 118.17847 458911.7 5438789.808658 118.16194
                                458911.7 5438789.764302 118.140961 458911.7 5438789.722215
                                118.115735 458911.7 5438789.682803 118.086505 458911.7
                                5438789.646447 118.053553 458911.7 5438789.613495 118.017197
                                458911.7 5438789.584265 117.977785 458911.7 5438789.559039
                                117.935698 458911.7 5438789.53806 117.891342 458911.7 5438789.52153
                                117.845142 458911.7 5438789.509607 117.797545 458911.7
                                5438789.502408 117.749009 458911.7 5438789.5 117.7 458911.7
                                5438789.502408 117.650991 458911.7 5438789.509607 117.602455
                                458911.7 5438789.520482 117.55904 458911.7 5438789.53806 117.508658
                                458911.7 5438789.559039 117.464302 458911.7 5438789.584265
                                117.422215 458911.7 5438789.613495 117.382803 458911.7
                                5438789.646447 117.346447 458911.7 5438789.682803 117.313495
                                458911.7 5438789.722215 117.284265 458911.7 5438789.764302
                                117.259039 458911.7 5438789.808658 117.23806 458911.7 5438789.854858
                                117.22153 458911.7 5438789.902455 117.209607 458911.7 5438789.950991
                                117.202408 458911.7 5438790.0 117.2 458911.7 5438790.049009
                                117.202408 458911.7 5438790.097545 117.209607 458911.7
                                5438790.145142 117.22153 458911.7 5438790.191342 117.23806 458911.7
                                5438790.235698 117.259039 458911.7 5438790.277785 117.284265
                                458911.7 5438790.317197 117.313495 458911.7 5438790.353553
                                117.346447 458911.7 5438790.386505 117.382803 458911.7
                                5438790.415735 117.422215 458911.7 5438790.440961 117.464302
                                458911.7 5438790.46194 117.508658 458911.7 5438790.47847 117.554858
                                458911.7 5438790.490393 117.602455 458911.7 5438790.497592
                                117.650991 458911.7 5438790.5 117.7 458911.7 5438790.497592
                                117.749009 458911.7 5438790.490393 117.797545 458911.7 5438790.47847
                                117.845142 458911.7 5438790.46194 117.891342 458911.7 5438790.440961
                                117.935698 458911.7 5438790.415735 117.977785 458911.7
                                5438790.386505 118.017197 458911.7 5438790.353553 118.053553
                                458911.7 5438790.317197 118.086505 458911.7 5438790.277785
                                118.115735 458911.7 5438790.235698 118.140961 458911.7
                                5438790.191342 118.16194 458911.7 5438790.145142 118.17847 458911.7
                                5438790.097545 118.190393 458911.7 5438790.049009 118.197592
                                458911.7 5438790.0 118.2</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.gEUqSoYeOFLY26aPvwVa">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_LR.BME13xGiI9U3Wt204amO">
                              <gml:posList srsDimension="3">458912.0 5438795.0 116.4 458912.0
                                5438795.0 116.9 458912.0 5438790.0 119.786751 458912.0 5438785.0
                                116.9 458912.0 5438785.0 116.4 458912.0 5438795.0
                                116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                          <gml:interior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_LR.iDrepQ9hvt1LcTm6hJYG">
                              <gml:posList srsDimension="3">458912.0 5438789.950991 118.197592
                                458912.0 5438790.0 118.2 458912.0 5438790.049009 118.197592 458912.0
                                5438790.097545 118.190393 458912.0 5438790.145142 118.17847 458912.0
                                5438790.191342 118.16194 458912.0 5438790.235698 118.140961 458912.0
                                5438790.277785 118.115735 458912.0 5438790.317197 118.086505
                                458912.0 5438790.353553 118.053553 458912.0 5438790.386505
                                118.017197 458912.0 5438790.415735 117.977785 458912.0
                                5438790.440961 117.935698 458912.0 5438790.46194 117.891342 458912.0
                                5438790.47847 117.845142 458912.0 5438790.490393 117.797545 458912.0
                                5438790.497592 117.749009 458912.0 5438790.5 117.7 458912.0
                                5438790.497592 117.650991 458912.0 5438790.490393 117.602455
                                458912.0 5438790.47847 117.554858 458912.0 5438790.46194 117.508658
                                458912.0 5438790.440961 117.464302 458912.0 5438790.415735
                                117.422215 458912.0 5438790.386505 117.382803 458912.0
                                5438790.353553 117.346447 458912.0 5438790.317197 117.313495
                                458912.0 5438790.277785 117.284265 458912.0 5438790.235698
                                117.259039 458912.0 5438790.191342 117.23806 458912.0 5438790.145142
                                117.22153 458912.0 5438790.097545 117.209607 458912.0 5438790.049009
                                117.202408 458912.0 5438790.0 117.2 458912.0 5438789.950991
                                117.202408 458912.0 5438789.902455 117.209607 458912.0
                                5438789.854858 117.22153 458912.0 5438789.808658 117.23806 458912.0
                                5438789.764302 117.259039 458912.0 5438789.722215 117.284265
                                458912.0 5438789.682803 117.313495 458912.0 5438789.646447
                                117.346447 458912.0 5438789.613495 117.382803 458912.0
                                5438789.584265 117.422215 458912.0 5438789.559039 117.464302
                                458912.0 5438789.53806 117.508658 458912.0 5438789.520482 117.55904
                                458912.0 5438789.509607 117.602455 458912.0 5438789.502408
                                117.650991 458912.0 5438789.5 117.7 458912.0 5438789.502408
                                117.749009 458912.0 5438789.509607 117.797545 458912.0 5438789.52153
                                117.845142 458912.0 5438789.53806 117.891342 458912.0 5438789.559039
                                117.935698 458912.0 5438789.584265 117.977785 458912.0
                                5438789.613495 118.017197 458912.0 5438789.646447 118.053553
                                458912.0 5438789.682803 118.086505 458912.0 5438789.722215
                                118.115735 458912.0 5438789.764302 118.140961 458912.0
                                5438789.808658 118.16194 458912.0 5438789.854858 118.17847 458912.0
                                5438789.902455 118.190393 458912.0 5438789.950991
                                118.197592</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.UVrxYZII6B07b0qMLJrH">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.0 118.2 458912.0
                                5438789.950991 118.197592 458911.7 5438789.950991 118.197592
                                458911.7 5438790.0 118.2 458912.0 5438790.0 118.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.UEsVvjvM5Jz8PYGCu8fy">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.950991 118.197592
                                458912.0 5438789.902455 118.190393 458911.7 5438789.902455
                                118.190393 458911.7 5438789.950991 118.197592 458912.0
                                5438789.950991 118.197592</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.6lihCSiX29syQkjRSItD">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.902455 118.190393
                                458912.0 5438789.854858 118.17847 458911.7 5438789.854858 118.17847
                                458911.7 5438789.902455 118.190393 458912.0 5438789.902455
                                118.190393</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.XVjic4mVD39DMieFeozC">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.854858 118.17847
                                458912.0 5438789.808658 118.16194 458911.7 5438789.808658 118.16194
                                458911.7 5438789.854858 118.17847 458912.0 5438789.854858
                                118.17847</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.cK7Qrhr6BbYvY2KiqAmX">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.808658 118.16194
                                458912.0 5438789.764302 118.140961 458911.7 5438789.764302
                                118.140961 458911.7 5438789.808658 118.16194 458912.0 5438789.808658
                                118.16194</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.7XVKzDCkWgUbYmcAVZsw">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.764302 118.140961
                                458912.0 5438789.722215 118.115735 458911.7 5438789.722215
                                118.115735 458911.7 5438789.764302 118.140961 458912.0
                                5438789.764302 118.140961</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.VEmwUZIgRr4PmgJQYTCE">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.722215 118.115735
                                458912.0 5438789.682803 118.086505 458911.7 5438789.682803
                                118.086505 458911.7 5438789.722215 118.115735 458912.0
                                5438789.722215 118.115735</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.32oKLqzJJuhPro9wzPxQ">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.682803 118.086505
                                458912.0 5438789.646447 118.053553 458911.7 5438789.646447
                                118.053553 458911.7 5438789.682803 118.086505 458912.0
                                5438789.682803 118.086505</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.WwoHLUHpTnrRGiXsBBpl">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.646447 118.053553
                                458912.0 5438789.613495 118.017197 458911.7 5438789.613495
                                118.017197 458911.7 5438789.646447 118.053553 458912.0
                                5438789.646447 118.053553</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.Br2AkE40jBPaztO4NK5c">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.613495 118.017197
                                458912.0 5438789.584265 117.977785 458911.7 5438789.584265
                                117.977785 458911.7 5438789.613495 118.017197 458912.0
                                5438789.613495 118.017197</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.Q3VRDplBcf5Sn8A7gJSe">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.584265 117.977785
                                458912.0 5438789.559039 117.935698 458911.7 5438789.559039
                                117.935698 458911.7 5438789.584265 117.977785 458912.0
                                5438789.584265 117.977785</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.JTtUUOecuPI2zWmffEdW">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.559039 117.935698
                                458912.0 5438789.53806 117.891342 458911.7 5438789.53806 117.891342
                                458911.7 5438789.559039 117.935698 458912.0 5438789.559039
                                117.935698</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.cmJhj4LtBVXujMI6c4fP">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.53806 117.891342
                                458912.0 5438789.52153 117.845142 458911.7 5438789.52153 117.845142
                                458911.7 5438789.53806 117.891342 458912.0 5438789.53806
                                117.891342</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.tEmaCEhbmqm9yc3olLdv">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.52153 117.845142
                                458912.0 5438789.509607 117.797545 458911.7 5438789.509607
                                117.797545 458911.7 5438789.52153 117.845142 458912.0 5438789.52153
                                117.845142</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.CSQGsLiLq3TR3QFz0zNh">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.509607 117.797545
                                458912.0 5438789.502408 117.749009 458911.7 5438789.502408
                                117.749009 458911.7 5438789.509607 117.797545 458912.0
                                5438789.509607 117.797545</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.7uCK71niQJNpSk6q6bQo">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.502408 117.749009
                                458912.0 5438789.5 117.7 458911.7 5438789.5 117.7 458911.7
                                5438789.502408 117.749009 458912.0 5438789.502408
                                117.749009</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.Yxco1ZKuRESx19QSj0Ec">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.5 117.7 458912.0
                                5438789.502408 117.650991 458911.7 5438789.502408 117.650991
                                458911.7 5438789.5 117.7 458912.0 5438789.5 117.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.6Wz85yeHKNQzPzl71hi2">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.502408 117.650991
                                458912.0 5438789.509607 117.602455 458911.7 5438789.509607
                                117.602455 458911.7 5438789.502408 117.650991 458912.0
                                5438789.502408 117.650991</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.XXDJ0dn3Utm5YQE82uIp">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.509607 117.602455
                                458912.0 5438789.520482 117.55904 458911.7 5438789.520482 117.55904
                                458911.7 5438789.509607 117.602455 458912.0 5438789.509607
                                117.602455</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.KEw8qErkzHoHmAdfFVNZ">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.520482 117.55904
                                458912.0 5438789.53806 117.508658 458911.7 5438789.53806 117.508658
                                458911.7 5438789.520482 117.55904 458912.0 5438789.520482
                                117.55904</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.yVYH5rtHSoKQiGJOg7g4">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.53806 117.508658
                                458912.0 5438789.559039 117.464302 458911.7 5438789.559039
                                117.464302 458911.7 5438789.53806 117.508658 458912.0 5438789.53806
                                117.508658</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.XzSoGRhq9BNX6v1nTE2B">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.559039 117.464302
                                458912.0 5438789.584265 117.422215 458911.7 5438789.584265
                                117.422215 458911.7 5438789.559039 117.464302 458912.0
                                5438789.559039 117.464302</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.4vBTyMX4CrNwX8AP8FXO">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.584265 117.422215
                                458912.0 5438789.613495 117.382803 458911.7 5438789.613495
                                117.382803 458911.7 5438789.584265 117.422215 458912.0
                                5438789.584265 117.422215</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.DMQvRTwMHeBvJNxvpNYk">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.613495 117.382803
                                458912.0 5438789.646447 117.346447 458911.7 5438789.646447
                                117.346447 458911.7 5438789.613495 117.382803 458912.0
                                5438789.613495 117.382803</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.WQbQrFJ08GbR9rDwF9Tj">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.646447 117.346447
                                458912.0 5438789.682803 117.313495 458911.7 5438789.682803
                                117.313495 458911.7 5438789.646447 117.346447 458912.0
                                5438789.646447 117.346447</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.NX0Kd1iQoq0sf5YQ5FCb">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.682803 117.313495
                                458912.0 5438789.722215 117.284265 458911.7 5438789.722215
                                117.284265 458911.7 5438789.682803 117.313495 458912.0
                                5438789.682803 117.313495</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.J9Fp8cQZDHeibcKpYA6M">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.722215 117.284265
                                458912.0 5438789.764302 117.259039 458911.7 5438789.764302
                                117.259039 458911.7 5438789.722215 117.284265 458912.0
                                5438789.722215 117.284265</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.3ydcErzYTjbEfxDkhJhh">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.764302 117.259039
                                458912.0 5438789.808658 117.23806 458911.7 5438789.808658 117.23806
                                458911.7 5438789.764302 117.259039 458912.0 5438789.764302
                                117.259039</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.b0ytGkB5KLl3yiTDwNQ5">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.808658 117.23806
                                458912.0 5438789.854858 117.22153 458911.7 5438789.854858 117.22153
                                458911.7 5438789.808658 117.23806 458912.0 5438789.808658
                                117.23806</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.WJEfneenBWpaTrlEBT3T">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.854858 117.22153
                                458912.0 5438789.902455 117.209607 458911.7 5438789.902455
                                117.209607 458911.7 5438789.854858 117.22153 458912.0 5438789.854858
                                117.22153</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.nExgADm8B1h386ydIETU">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.902455 117.209607
                                458912.0 5438789.950991 117.202408 458911.7 5438789.950991
                                117.202408 458911.7 5438789.902455 117.209607 458912.0
                                5438789.902455 117.209607</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.3gfu9ZHLlmAI5f2PGNzl">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438789.950991 117.202408
                                458912.0 5438790.0 117.2 458911.7 5438790.0 117.2 458911.7
                                5438789.950991 117.202408 458912.0 5438789.950991
                                117.202408</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.EtTRgHKjral4sltWvrnn">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.0 117.2 458912.0
                                5438790.049009 117.202408 458911.7 5438790.049009 117.202408
                                458911.7 5438790.0 117.2 458912.0 5438790.0 117.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.oRHkWlGVSz67ZJEylnUJ">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.049009 117.202408
                                458912.0 5438790.097545 117.209607 458911.7 5438790.097545
                                117.209607 458911.7 5438790.049009 117.202408 458912.0
                                5438790.049009 117.202408</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.GOKaBV66BjDiQcEmftsA">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.097545 117.209607
                                458912.0 5438790.145142 117.22153 458911.7 5438790.145142 117.22153
                                458911.7 5438790.097545 117.209607 458912.0 5438790.097545
                                117.209607</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.F3YqqiO6CHw36e7hFQ3Q">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.145142 117.22153
                                458912.0 5438790.191342 117.23806 458911.7 5438790.191342 117.23806
                                458911.7 5438790.145142 117.22153 458912.0 5438790.145142
                                117.22153</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.lojs9PFJ38v0Ac2FlayC">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.191342 117.23806
                                458912.0 5438790.235698 117.259039 458911.7 5438790.235698
                                117.259039 458911.7 5438790.191342 117.23806 458912.0 5438790.191342
                                117.23806</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.hOsB4PbVnX0n6AJWJP4T">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.235698 117.259039
                                458912.0 5438790.277785 117.284265 458911.7 5438790.277785
                                117.284265 458911.7 5438790.235698 117.259039 458912.0
                                5438790.235698 117.259039</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.JHj2MHKpOhSxeyqTZAXz">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.277785 117.284265
                                458912.0 5438790.317197 117.313495 458911.7 5438790.317197
                                117.313495 458911.7 5438790.277785 117.284265 458912.0
                                5438790.277785 117.284265</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.N9W5smybE3KLTUYlVY3J">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.317197 117.313495
                                458912.0 5438790.353553 117.346447 458911.7 5438790.353553
                                117.346447 458911.7 5438790.317197 117.313495 458912.0
                                5438790.317197 117.313495</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.gO0UK2sWLNbx8VWU2orT">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.353553 117.346447
                                458912.0 5438790.386505 117.382803 458911.7 5438790.386505
                                117.382803 458911.7 5438790.353553 117.346447 458912.0
                                5438790.353553 117.346447</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.vt8nuJSwRSBSaS4WynMx">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.386505 117.382803
                                458912.0 5438790.415735 117.422215 458911.7 5438790.415735
                                117.422215 458911.7 5438790.386505 117.382803 458912.0
                                5438790.386505 117.382803</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.npdFCZK2weUEYSC1WxOs">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.415735 117.422215
                                458912.0 5438790.440961 117.464302 458911.7 5438790.440961
                                117.464302 458911.7 5438790.415735 117.422215 458912.0
                                5438790.415735 117.422215</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.ikJAa67vOHW4LNHsJiZP">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.440961 117.464302
                                458912.0 5438790.46194 117.508658 458911.7 5438790.46194 117.508658
                                458911.7 5438790.440961 117.464302 458912.0 5438790.440961
                                117.464302</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.0hbjpY12KJgwMDw4gXXf">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.46194 117.508658
                                458912.0 5438790.47847 117.554858 458911.7 5438790.47847 117.554858
                                458911.7 5438790.46194 117.508658 458912.0 5438790.46194
                                117.508658</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.ZM7uRaMR6epZv4nbEoKc">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.47847 117.554858
                                458912.0 5438790.490393 117.602455 458911.7 5438790.490393
                                117.602455 458911.7 5438790.47847 117.554858 458912.0 5438790.47847
                                117.554858</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.xCH1FMvSuWoKTD8Jgc6a">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.490393 117.602455
                                458912.0 5438790.497592 117.650991 458911.7 5438790.497592
                                117.650991 458911.7 5438790.490393 117.602455 458912.0
                                5438790.490393 117.602455</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.ygnnB5QxYl2s6xA1JZfV">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.497592 117.650991
                                458912.0 5438790.5 117.7 458911.7 5438790.5 117.7 458911.7
                                5438790.497592 117.650991 458912.0 5438790.497592
                                117.650991</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.KF35NJJqUDA8D49R0CNi">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.5 117.7 458912.0
                                5438790.497592 117.749009 458911.7 5438790.497592 117.749009
                                458911.7 5438790.5 117.7 458912.0 5438790.5 117.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.Q7nGcN8I200dKCydPhPU">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.497592 117.749009
                                458912.0 5438790.490393 117.797545 458911.7 5438790.490393
                                117.797545 458911.7 5438790.497592 117.749009 458912.0
                                5438790.497592 117.749009</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.q52JInCbEMGS9IlmcvAE">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.490393 117.797545
                                458912.0 5438790.47847 117.845142 458911.7 5438790.47847 117.845142
                                458911.7 5438790.490393 117.797545 458912.0 5438790.490393
                                117.797545</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.UGeS0MvCsvAQApaMN7Cz">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.47847 117.845142
                                458912.0 5438790.46194 117.891342 458911.7 5438790.46194 117.891342
                                458911.7 5438790.47847 117.845142 458912.0 5438790.47847
                                117.845142</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.oPZesjL2cR2Ep4JgWH4q">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.46194 117.891342
                                458912.0 5438790.440961 117.935698 458911.7 5438790.440961
                                117.935698 458911.7 5438790.46194 117.891342 458912.0 5438790.46194
                                117.891342</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.ExfgmrmOYW8V4p5KKYuq">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.440961 117.935698
                                458912.0 5438790.415735 117.977785 458911.7 5438790.415735
                                117.977785 458911.7 5438790.440961 117.935698 458912.0
                                5438790.440961 117.935698</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.d7SHai1vlIzwTYXRwrRO">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.415735 117.977785
                                458912.0 5438790.386505 118.017197 458911.7 5438790.386505
                                118.017197 458911.7 5438790.415735 117.977785 458912.0
                                5438790.415735 117.977785</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.2QP3AcH9syeNWcs2ycek">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.386505 118.017197
                                458912.0 5438790.353553 118.053553 458911.7 5438790.353553
                                118.053553 458911.7 5438790.386505 118.017197 458912.0
                                5438790.386505 118.017197</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.BpYJrR0aijAoaupYr1t0">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.353553 118.053553
                                458912.0 5438790.317197 118.086505 458911.7 5438790.317197
                                118.086505 458911.7 5438790.353553 118.053553 458912.0
                                5438790.353553 118.053553</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.QUdrRF2GFKFWxCqaL03v">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.317197 118.086505
                                458912.0 5438790.277785 118.115735 458911.7 5438790.277785
                                118.115735 458911.7 5438790.317197 118.086505 458912.0
                                5438790.317197 118.086505</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.CFmcf6rQMPyaT8Bd1NNx">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.277785 118.115735
                                458912.0 5438790.235698 118.140961 458911.7 5438790.235698
                                118.140961 458911.7 5438790.277785 118.115735 458912.0
                                5438790.277785 118.115735</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.P42tyRKb1TZPnnNyIPQZ">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.235698 118.140961
                                458912.0 5438790.191342 118.16194 458911.7 5438790.191342 118.16194
                                458911.7 5438790.235698 118.140961 458912.0 5438790.235698
                                118.140961</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.o5DM4dQHJi8AxeXJrjWd">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.191342 118.16194
                                458912.0 5438790.145142 118.17847 458911.7 5438790.145142 118.17847
                                458911.7 5438790.191342 118.16194 458912.0 5438790.191342
                                118.16194</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.zTR9KD9pVT0SAHLpJ0ms">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.145142 118.17847
                                458912.0 5438790.097545 118.190393 458911.7 5438790.097545
                                118.190393 458911.7 5438790.145142 118.17847 458912.0 5438790.145142
                                118.17847</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.U1Zj8M2rxDi24SDg5w8T">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.097545 118.190393
                                458912.0 5438790.049009 118.197592 458911.7 5438790.049009
                                118.197592 458911.7 5438790.097545 118.190393 458912.0
                                5438790.097545 118.190393</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.rR9jsnKpjJdrkuWAtWdg">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438790.049009 118.197592
                                458912.0 5438790.0 118.2 458911.7 5438790.0 118.2 458911.7
                                5438790.049009 118.197592 458912.0 5438790.049009
                                118.197592</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </core:lod2Solid>
              <con:isStructuralElement>true</con:isStructuralElement>
              <con:filling>
                <con:Window
                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.1j3CFxYaBLINTZb5QAjF">
                  <gml:name>18 - Second Floor Window01 East</gml:name>
                  <core:lod2Solid>
                    <gml:Solid>
                      <gml:exterior>
                        <gml:Shell>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.509607 117.602455
                                    458911.7 5438789.52153 117.554858 458912.0 5438789.520482
                                    117.55904 458912.0 5438789.509607 117.602455 458911.7
                                    5438789.509607 117.602455</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.764302 117.259039
                                    458912.0 5438789.764302 117.259039 458912.0 5438789.722215
                                    117.284265 458911.7 5438789.722215 117.284265 458911.7
                                    5438789.764302 117.259039</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.902455 118.190393
                                    458912.0 5438789.902455 118.190393 458912.0 5438789.950991
                                    118.197592 458911.7 5438789.950991 118.197592 458911.7
                                    5438789.902455 118.190393</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.902455 117.209607
                                    458912.0 5438789.902455 117.209607 458912.0 5438789.854858
                                    117.22153 458911.7 5438789.854858 117.22153 458911.7
                                    5438789.902455 117.209607</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.5 117.7 458912.0
                                    5438790.5 117.7 458912.0 5438790.497592 117.650991 458911.7
                                    5438790.497592 117.650991 458911.7 5438790.5 117.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.722215 117.284265
                                    458912.0 5438789.722215 117.284265 458912.0 5438789.682803
                                    117.313495 458911.7 5438789.682803 117.313495 458911.7
                                    5438789.722215 117.284265</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.808658 117.23806
                                    458912.0 5438789.808658 117.23806 458912.0 5438789.764302
                                    117.259039 458911.7 5438789.764302 117.259039 458911.7
                                    5438789.808658 117.23806</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.764302 118.140961
                                    458912.0 5438789.764302 118.140961 458912.0 5438789.808658
                                    118.16194 458911.7 5438789.808658 118.16194 458911.7
                                    5438789.764302 118.140961</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.317197 117.313495
                                    458912.0 5438790.317197 117.313495 458912.0 5438790.277785
                                    117.284265 458911.7 5438790.277785 117.284265 458911.7
                                    5438790.317197 117.313495</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.854858 118.17847
                                    458912.0 5438789.854858 118.17847 458912.0 5438789.902455
                                    118.190393 458911.7 5438789.902455 118.190393 458911.7
                                    5438789.854858 118.17847</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.584265 117.422215
                                    458912.0 5438789.584265 117.422215 458912.0 5438789.559039
                                    117.464302 458911.7 5438789.559039 117.464302 458911.7
                                    5438789.584265 117.422215</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.145142 117.22153
                                    458912.0 5438790.145142 117.22153 458912.0 5438790.097545
                                    117.209607 458911.7 5438790.097545 117.209607 458911.7
                                    5438790.145142 117.22153</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.353553 117.346447
                                    458912.0 5438790.353553 117.346447 458912.0 5438790.317197
                                    117.313495 458911.7 5438790.317197 117.313495 458911.7
                                    5438790.353553 117.346447</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.277785 118.115735
                                    458912.0 5438790.277785 118.115735 458912.0 5438790.317197
                                    118.086505 458911.7 5438790.317197 118.086505 458911.7
                                    5438790.277785 118.115735</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.509607 117.797545
                                    458912.0 5438789.509607 117.797545 458912.0 5438789.52153
                                    117.845142 458911.7 5438789.52153 117.845142 458911.7
                                    5438789.509607 117.797545</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.808658 118.16194
                                    458912.0 5438789.808658 118.16194 458912.0 5438789.854858
                                    118.17847 458911.7 5438789.854858 118.17847 458911.7
                                    5438789.808658 118.16194</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.415735 117.977785
                                    458912.0 5438790.415735 117.977785 458912.0 5438790.440961
                                    117.935698 458911.7 5438790.440961 117.935698 458911.7
                                    5438790.415735 117.977785</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.145142 118.17847
                                    458912.0 5438790.145142 118.17847 458912.0 5438790.191342
                                    118.16194 458911.7 5438790.191342 118.16194 458911.7
                                    5438790.145142 118.17847</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.353553 118.053553
                                    458912.0 5438790.353553 118.053553 458912.0 5438790.386505
                                    118.017197 458911.7 5438790.386505 118.017197 458911.7
                                    5438790.353553 118.053553</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.440961 117.464302
                                    458912.0 5438790.440961 117.464302 458912.0 5438790.415735
                                    117.422215 458911.7 5438790.415735 117.422215 458911.7
                                    5438790.440961 117.464302</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.46194 117.891342
                                    458912.0 5438790.46194 117.891342 458912.0 5438790.47847
                                    117.845142 458911.7 5438790.47847 117.845142 458911.7
                                    5438790.46194 117.891342</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.0 118.2 458912.0
                                    5438790.0 118.2 458912.0 5438790.049009 118.197592 458911.7
                                    5438790.049009 118.197592 458911.7 5438790.0 118.2</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.613495 118.017197
                                    458912.0 5438789.613495 118.017197 458912.0 5438789.646447
                                    118.053553 458911.7 5438789.646447 118.053553 458911.7
                                    5438789.613495 118.017197</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.46194 117.508658
                                    458912.0 5438790.46194 117.508658 458912.0 5438790.440961
                                    117.464302 458911.7 5438790.440961 117.464302 458911.7
                                    5438790.46194 117.508658</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.490393 117.797545
                                    458912.0 5438790.490393 117.797545 458912.0 5438790.497592
                                    117.749009 458911.7 5438790.497592 117.749009 458911.7
                                    5438790.490393 117.797545</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.613495 117.382803
                                    458912.0 5438789.613495 117.382803 458912.0 5438789.584265
                                    117.422215 458911.7 5438789.584265 117.422215 458911.7
                                    5438789.613495 117.382803</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.559039 117.935698
                                    458912.0 5438789.559039 117.935698 458912.0 5438789.584265
                                    117.977785 458911.7 5438789.584265 117.977785 458911.7
                                    5438789.559039 117.935698</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.722215 118.115735
                                    458912.0 5438789.722215 118.115735 458912.0 5438789.764302
                                    118.140961 458911.7 5438789.764302 118.140961 458911.7
                                    5438789.722215 118.115735</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.854858 117.22153
                                    458912.0 5438789.854858 117.22153 458912.0 5438789.808658
                                    117.23806 458911.7 5438789.808658 117.23806 458911.7
                                    5438789.854858 117.22153</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.646447 118.053553
                                    458912.0 5438789.646447 118.053553 458912.0 5438789.682803
                                    118.086505 458911.7 5438789.682803 118.086505 458911.7
                                    5438789.646447 118.053553</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.584265 117.977785
                                    458912.0 5438789.584265 117.977785 458912.0 5438789.613495
                                    118.017197 458911.7 5438789.613495 118.017197 458911.7
                                    5438789.584265 117.977785</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.950991 118.197592
                                    458912.0 5438789.950991 118.197592 458912.0 5438790.0 118.2
                                    458911.7 5438790.0 118.2 458911.7 5438789.950991
                                    118.197592</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.440961 117.935698
                                    458912.0 5438790.440961 117.935698 458912.0 5438790.46194
                                    117.891342 458911.7 5438790.46194 117.891342 458911.7
                                    5438790.440961 117.935698</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.502408 117.650991
                                    458912.0 5438789.502408 117.650991 458912.0 5438789.5 117.7
                                    458911.7 5438789.5 117.7 458911.7 5438789.502408
                                    117.650991</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.1j3CFxYaBLINTZb5QAjF_PG.clckEsEN2ccOxgWjKQwZ">
                              <gml:exterior>
                                <gml:LinearRing
                                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.1j3CFxYaBLINTZb5QAjF_LR.fVLFGc1zHqrJPkxisCO1">
                                  <gml:posList srsDimension="3">458912.0 5438790.353553 118.053553
                                    458912.0 5438790.317197 118.086505 458912.0 5438790.277785
                                    118.115735 458912.0 5438790.235698 118.140961 458912.0
                                    5438790.191342 118.16194 458912.0 5438790.145142 118.17847
                                    458912.0 5438790.097545 118.190393 458912.0 5438790.049009
                                    118.197592 458912.0 5438790.0 118.2 458912.0 5438789.950991
                                    118.197592 458912.0 5438789.902455 118.190393 458912.0
                                    5438789.854858 118.17847 458912.0 5438789.808658 118.16194
                                    458912.0 5438789.764302 118.140961 458912.0 5438789.722215
                                    118.115735 458912.0 5438789.682803 118.086505 458912.0
                                    5438789.646447 118.053553 458912.0 5438789.613495 118.017197
                                    458912.0 5438789.584265 117.977785 458912.0 5438789.559039
                                    117.935698 458912.0 5438789.53806 117.891342 458912.0
                                    5438789.52153 117.845142 458912.0 5438789.509607 117.797545
                                    458912.0 5438789.502408 117.749009 458912.0 5438789.5 117.7
                                    458912.0 5438789.502408 117.650991 458912.0 5438789.509607
                                    117.602455 458912.0 5438789.520482 117.55904 458912.0
                                    5438789.53806 117.508658 458912.0 5438789.559039 117.464302
                                    458912.0 5438789.584265 117.422215 458912.0 5438789.613495
                                    117.382803 458912.0 5438789.646447 117.346447 458912.0
                                    5438789.682803 117.313495 458912.0 5438789.722215 117.284265
                                    458912.0 5438789.764302 117.259039 458912.0 5438789.808658
                                    117.23806 458912.0 5438789.854858 117.22153 458912.0
                                    5438789.902455 117.209607 458912.0 5438789.950991 117.202408
                                    458912.0 5438790.0 117.2 458912.0 5438790.049009 117.202408
                                    458912.0 5438790.097545 117.209607 458912.0 5438790.145142
                                    117.22153 458912.0 5438790.191342 117.23806 458912.0
                                    5438790.235698 117.259039 458912.0 5438790.277785 117.284265
                                    458912.0 5438790.317197 117.313495 458912.0 5438790.353553
                                    117.346447 458912.0 5438790.386505 117.382803 458912.0
                                    5438790.415735 117.422215 458912.0 5438790.440961 117.464302
                                    458912.0 5438790.46194 117.508658 458912.0 5438790.47847
                                    117.554858 458912.0 5438790.490393 117.602455 458912.0
                                    5438790.497592 117.650991 458912.0 5438790.5 117.7 458912.0
                                    5438790.497592 117.749009 458912.0 5438790.490393 117.797545
                                    458912.0 5438790.47847 117.845142 458912.0 5438790.46194
                                    117.891342 458912.0 5438790.440961 117.935698 458912.0
                                    5438790.415735 117.977785 458912.0 5438790.386505 118.017197
                                    458912.0 5438790.353553 118.053553</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.646447 117.346447
                                    458912.0 5438789.646447 117.346447 458912.0 5438789.613495
                                    117.382803 458911.7 5438789.613495 117.382803 458911.7
                                    5438789.646447 117.346447</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.049009 118.197592
                                    458912.0 5438790.049009 118.197592 458912.0 5438790.097545
                                    118.190393 458911.7 5438790.097545 118.190393 458911.7
                                    5438790.049009 118.197592</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.53806 117.508658
                                    458911.7 5438789.52153 117.554858 458911.7 5438789.509607
                                    117.602455 458911.7 5438789.502408 117.650991 458911.7 5438789.5
                                    117.7 458911.7 5438789.502408 117.749009 458911.7 5438789.509607
                                    117.797545 458911.7 5438789.52153 117.845142 458911.7
                                    5438789.53806 117.891342 458911.7 5438789.559039 117.935698
                                    458911.7 5438789.584265 117.977785 458911.7 5438789.613495
                                    118.017197 458911.7 5438789.646447 118.053553 458911.7
                                    5438789.682803 118.086505 458911.7 5438789.722215 118.115735
                                    458911.7 5438789.764302 118.140961 458911.7 5438789.808658
                                    118.16194 458911.7 5438789.854858 118.17847 458911.7
                                    5438789.902455 118.190393 458911.7 5438789.950991 118.197592
                                    458911.7 5438790.0 118.2 458911.7 5438790.049009 118.197592
                                    458911.7 5438790.097545 118.190393 458911.7 5438790.145142
                                    118.17847 458911.7 5438790.191342 118.16194 458911.7
                                    5438790.235698 118.140961 458911.7 5438790.277785 118.115735
                                    458911.7 5438790.317197 118.086505 458911.7 5438790.353553
                                    118.053553 458911.7 5438790.386505 118.017197 458911.7
                                    5438790.415735 117.977785 458911.7 5438790.440961 117.935698
                                    458911.7 5438790.46194 117.891342 458911.7 5438790.47847
                                    117.845142 458911.7 5438790.490393 117.797545 458911.7
                                    5438790.497592 117.749009 458911.7 5438790.5 117.7 458911.7
                                    5438790.497592 117.650991 458911.7 5438790.490393 117.602455
                                    458911.7 5438790.47847 117.554858 458911.7 5438790.46194
                                    117.508658 458911.7 5438790.440961 117.464302 458911.7
                                    5438790.415735 117.422215 458911.7 5438790.386505 117.382803
                                    458911.7 5438790.353553 117.346447 458911.7 5438790.317197
                                    117.313495 458911.7 5438790.277785 117.284265 458911.7
                                    5438790.235698 117.259039 458911.7 5438790.191342 117.23806
                                    458911.7 5438790.145142 117.22153 458911.7 5438790.097545
                                    117.209607 458911.7 5438790.049009 117.202408 458911.7 5438790.0
                                    117.2 458911.7 5438789.950991 117.202408 458911.7 5438789.902455
                                    117.209607 458911.7 5438789.854858 117.22153 458911.7
                                    5438789.808658 117.23806 458911.7 5438789.764302 117.259039
                                    458911.7 5438789.722215 117.284265 458911.7 5438789.682803
                                    117.313495 458911.7 5438789.646447 117.346447 458911.7
                                    5438789.613495 117.382803 458911.7 5438789.584265 117.422215
                                    458911.7 5438789.559039 117.464302 458911.7 5438789.53806
                                    117.508658</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.682803 118.086505
                                    458912.0 5438789.682803 118.086505 458912.0 5438789.722215
                                    118.115735 458911.7 5438789.722215 118.115735 458911.7
                                    5438789.682803 118.086505</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.5 117.7 458912.0
                                    5438789.5 117.7 458912.0 5438789.502408 117.749009 458911.7
                                    5438789.502408 117.749009 458911.7 5438789.5 117.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.950991 117.202408
                                    458912.0 5438789.950991 117.202408 458912.0 5438789.902455
                                    117.209607 458911.7 5438789.902455 117.209607 458911.7
                                    5438789.950991 117.202408</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.049009 117.202408
                                    458912.0 5438790.049009 117.202408 458912.0 5438790.0 117.2
                                    458911.7 5438790.0 117.2 458911.7 5438790.049009
                                    117.202408</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.502408 117.749009
                                    458912.0 5438789.502408 117.749009 458912.0 5438789.509607
                                    117.797545 458911.7 5438789.509607 117.797545 458911.7
                                    5438789.502408 117.749009</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.097545 117.209607
                                    458912.0 5438790.097545 117.209607 458912.0 5438790.049009
                                    117.202408 458911.7 5438790.049009 117.202408 458911.7
                                    5438790.097545 117.209607</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.682803 117.313495
                                    458912.0 5438789.682803 117.313495 458912.0 5438789.646447
                                    117.346447 458911.7 5438789.646447 117.346447 458911.7
                                    5438789.682803 117.313495</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.191342 118.16194
                                    458912.0 5438790.191342 118.16194 458912.0 5438790.235698
                                    118.140961 458911.7 5438790.235698 118.140961 458911.7
                                    5438790.191342 118.16194</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.497592 117.749009
                                    458912.0 5438790.497592 117.749009 458912.0 5438790.5 117.7
                                    458911.7 5438790.5 117.7 458911.7 5438790.497592
                                    117.749009</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.386505 118.017197
                                    458912.0 5438790.386505 118.017197 458912.0 5438790.415735
                                    117.977785 458911.7 5438790.415735 117.977785 458911.7
                                    5438790.386505 118.017197</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.097545 118.190393
                                    458912.0 5438790.097545 118.190393 458912.0 5438790.145142
                                    118.17847 458911.7 5438790.145142 118.17847 458911.7
                                    5438790.097545 118.190393</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.317197 118.086505
                                    458912.0 5438790.317197 118.086505 458912.0 5438790.353553
                                    118.053553 458911.7 5438790.353553 118.053553 458911.7
                                    5438790.317197 118.086505</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.415735 117.422215
                                    458912.0 5438790.415735 117.422215 458912.0 5438790.386505
                                    117.382803 458911.7 5438790.386505 117.382803 458911.7
                                    5438790.415735 117.422215</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.52153 117.845142
                                    458912.0 5438789.52153 117.845142 458912.0 5438789.53806
                                    117.891342 458911.7 5438789.53806 117.891342 458911.7
                                    5438789.52153 117.845142</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.0 117.2 458912.0
                                    5438790.0 117.2 458912.0 5438789.950991 117.202408 458911.7
                                    5438789.950991 117.202408 458911.7 5438790.0 117.2</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.509607 117.602455
                                    458912.0 5438789.509607 117.602455 458912.0 5438789.502408
                                    117.650991 458911.7 5438789.502408 117.650991 458911.7
                                    5438789.509607 117.602455</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.386505 117.382803
                                    458912.0 5438790.386505 117.382803 458912.0 5438790.353553
                                    117.346447 458911.7 5438790.353553 117.346447 458911.7
                                    5438790.386505 117.382803</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.497592 117.650991
                                    458912.0 5438790.497592 117.650991 458912.0 5438790.490393
                                    117.602455 458911.7 5438790.490393 117.602455 458911.7
                                    5438790.497592 117.650991</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.47847 117.845142
                                    458912.0 5438790.47847 117.845142 458912.0 5438790.490393
                                    117.797545 458911.7 5438790.490393 117.797545 458911.7
                                    5438790.47847 117.845142</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.53806 117.891342
                                    458912.0 5438789.53806 117.891342 458912.0 5438789.559039
                                    117.935698 458911.7 5438789.559039 117.935698 458911.7
                                    5438789.53806 117.891342</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.47847 117.554858
                                    458912.0 5438790.47847 117.554858 458912.0 5438790.46194
                                    117.508658 458911.7 5438790.46194 117.508658 458911.7
                                    5438790.47847 117.554858</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.235698 118.140961
                                    458912.0 5438790.235698 118.140961 458912.0 5438790.277785
                                    118.115735 458911.7 5438790.277785 118.115735 458911.7
                                    5438790.235698 118.140961</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458912.0 5438789.53806 117.508658
                                    458911.7 5438789.53806 117.508658 458911.7 5438789.559039
                                    117.464302 458912.0 5438789.559039 117.464302 458912.0
                                    5438789.53806 117.508658</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438789.53806 117.508658
                                    458912.0 5438789.520482 117.55904 458911.7 5438789.52153
                                    117.554858 458911.7 5438789.53806 117.508658</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.490393 117.602455
                                    458912.0 5438790.490393 117.602455 458912.0 5438790.47847
                                    117.554858 458911.7 5438790.47847 117.554858 458911.7
                                    5438790.490393 117.602455</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.235698 117.259039
                                    458912.0 5438790.235698 117.259039 458912.0 5438790.191342
                                    117.23806 458911.7 5438790.191342 117.23806 458911.7
                                    5438790.235698 117.259039</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.277785 117.284265
                                    458912.0 5438790.277785 117.284265 458912.0 5438790.235698
                                    117.259039 458911.7 5438790.235698 117.259039 458911.7
                                    5438790.277785 117.284265</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458912.0 5438789.520482 117.55904
                                    458911.7 5438789.53806 117.508658 458912.0 5438789.53806
                                    117.508658 458912.0 5438789.520482 117.55904</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458911.7 5438790.191342 117.23806
                                    458912.0 5438790.191342 117.23806 458912.0 5438790.145142
                                    117.22153 458911.7 5438790.145142 117.22153 458911.7
                                    5438790.191342 117.23806</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                        </gml:Shell>
                      </gml:exterior>
                    </gml:Solid>
                  </core:lod2Solid>
                  <con:class>Window</con:class>
                </con:Window>
              </con:filling>
              <bldg:class>Wall</bldg:class>
            </bldg:BuildingConstructiveElement>
          </bldg:buildingConstructiveElement>
          <bldg:buildingConstructiveElement>
            <bldg:BuildingConstructiveElement
              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf">
              <gml:name>08 - Second Floor Wall North</gml:name>
              <core:lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_PG.jNQboPa0u7w243GPebem">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438794.7 116.4 458900.3
                                5438794.7 116.4 458900.0 5438795.0 116.4 458912.0 5438795.0 116.4
                                458911.7 5438794.7 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_PG.EirHVMjm9hy5SkvMdLy0">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438794.7 116.4 458900.3
                                5438794.7 117.073205 458900.0 5438795.0 116.9 458900.0 5438795.0
                                116.4 458900.3 5438794.7 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_PG.CfVzf3WfhmyHf8PYo4JS">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458912.0 5438795.0 116.4 458912.0
                                5438795.0 116.9 458911.7 5438794.7 117.073205 458911.7 5438794.7
                                116.4 458912.0 5438795.0 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_PG.XnYHk4ccnzcYlu8QmWho">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438794.7 117.073205 458911.7
                                5438794.7 117.073205 458912.0 5438795.0 116.9 458900.0 5438795.0
                                116.9 458900.3 5438794.7 117.073205</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_PG.7BAluzsqrefXamIThALm">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438794.7 117.073205 458900.3
                                5438794.7 117.073205 458900.3 5438794.7 116.4 458911.7 5438794.7
                                116.4 458911.7 5438794.7 117.073205</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_PG.6s7V4a1OB8u1aTStTcbJ">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_LR.ojQ6g83dDnYM4v1IhtAg">
                              <gml:posList srsDimension="3">458900.0 5438795.0 116.4 458900.0
                                5438795.0 116.9 458912.0 5438795.0 116.9 458912.0 5438795.0 116.4
                                458900.0 5438795.0 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </core:lod2Solid>
              <con:isStructuralElement>true</con:isStructuralElement>
              <bldg:class>Wall</bldg:class>
            </bldg:BuildingConstructiveElement>
          </bldg:buildingConstructiveElement>
          <bldg:buildingConstructiveElement>
            <bldg:BuildingConstructiveElement
              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9">
              <gml:name>09 - Second Floor Wall South</gml:name>
              <core:lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_PG.DAmp37PMEKiVkGsL0ms6">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438785.3 116.4 458911.7
                                5438785.3 116.4 458912.0 5438785.0 116.4 458900.0 5438785.0 116.4
                                458900.3 5438785.3 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_PG.l6nc2LexYlHeDl7BXm0N">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438785.3 117.073205 458912.0
                                5438785.0 116.9 458912.0 5438785.0 116.4 458911.7 5438785.3 116.4
                                458911.7 5438785.3 117.073205</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_PG.HaQve8yxYRhl4EcMD55u">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438785.0 116.9 458900.3
                                5438785.3 117.073205 458900.3 5438785.3 116.4 458900.0 5438785.0
                                116.4 458900.0 5438785.0 116.9</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_PG.o2m6wWfVQq6z9PpRino3">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438785.3 117.073205 458900.3
                                5438785.3 117.073205 458900.0 5438785.0 116.9 458912.0 5438785.0
                                116.9 458911.7 5438785.3 117.073205</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_PG.QZv6P5CusqLtsdu3RFf7">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438785.3 117.073205 458911.7
                                5438785.3 117.073205 458911.7 5438785.3 116.4 458900.3 5438785.3
                                116.4 458900.3 5438785.3 117.073205</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_PG.2dKXmAy0meKvCww51jj9">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_LR.0sdBO8XZL209jw1TNaGt">
                              <gml:posList srsDimension="3">458912.0 5438785.0 116.4 458912.0
                                5438785.0 116.9 458900.0 5438785.0 116.9 458900.0 5438785.0 116.4
                                458912.0 5438785.0 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </core:lod2Solid>
              <con:isStructuralElement>true</con:isStructuralElement>
              <bldg:class>Wall</bldg:class>
            </bldg:BuildingConstructiveElement>
          </bldg:buildingConstructiveElement>
          <bldg:buildingConstructiveElement>
            <bldg:BuildingConstructiveElement
              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9">
              <gml:name>10 - Second Floor Wall West</gml:name>
              <core:lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.xsKWsYE4QDecGyP5gnoP">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438794.7 116.4 458900.3
                                5438785.3 116.4 458900.0 5438785.0 116.4 458900.0 5438795.0 116.4
                                458900.3 5438794.7 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.GJKHOoZjPUWGT7WmvtYo">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438785.3 116.4 458900.3
                                5438785.3 117.073205 458900.0 5438785.0 116.9 458900.0 5438785.0
                                116.4 458900.3 5438785.3 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.eFksVmNchId214tQlSQ4">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438795.0 116.9 458900.3
                                5438794.7 117.073205 458900.3 5438794.7 116.4 458900.0 5438795.0
                                116.4 458900.0 5438795.0 116.9</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.OyfNYZGU0Gq9iRGhIeLN">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438785.0 116.9 458900.3
                                5438785.3 117.073205 458900.3 5438790.0 119.786751 458900.0
                                5438790.0 119.786751 458900.0 5438785.0 116.9</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.nLQJjcyjN5v5GPOwLZHS">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438790.0 119.786751 458900.3
                                5438794.7 117.073205 458900.0 5438795.0 116.9 458900.0 5438790.0
                                119.786751 458900.3 5438790.0 119.786751</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.5oRrsKRU1HWXsxniKHPy">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438785.3 117.073205 458900.3
                                5438785.3 116.4 458900.3 5438794.7 116.4 458900.3 5438794.7
                                117.073205 458900.3 5438790.0 119.786751 458900.3 5438785.3
                                117.073205</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                          <gml:interior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438790.386505 118.017197
                                458900.3 5438790.415735 117.977785 458900.3 5438790.440961
                                117.935698 458900.3 5438790.46194 117.891342 458900.3 5438790.47847
                                117.845142 458900.3 5438790.490393 117.797545 458900.3
                                5438790.497592 117.749009 458900.3 5438790.5 117.7 458900.3
                                5438790.497592 117.650991 458900.3 5438790.490393 117.602455
                                458900.3 5438790.47847 117.554858 458900.3 5438790.46194 117.508658
                                458900.3 5438790.440961 117.464302 458900.3 5438790.415735
                                117.422215 458900.3 5438790.386505 117.382803 458900.3
                                5438790.353553 117.346447 458900.3 5438790.317197 117.313495
                                458900.3 5438790.277785 117.284265 458900.3 5438790.235698
                                117.259039 458900.3 5438790.191342 117.23806 458900.3 5438790.145142
                                117.22153 458900.3 5438790.097545 117.209607 458900.3 5438790.049009
                                117.202408 458900.3 5438790.0 117.2 458900.3 5438789.950991
                                117.202408 458900.3 5438789.902455 117.209607 458900.3
                                5438789.854858 117.22153 458900.3 5438789.808658 117.23806 458900.3
                                5438789.764302 117.259039 458900.3 5438789.722215 117.284265
                                458900.3 5438789.682803 117.313495 458900.3 5438789.646447
                                117.346447 458900.3 5438789.613495 117.382803 458900.3
                                5438789.584265 117.422215 458900.3 5438789.559039 117.464302
                                458900.3 5438789.53806 117.508658 458900.3 5438789.52153 117.554858
                                458900.3 5438789.509607 117.602455 458900.3 5438789.502408
                                117.650991 458900.3 5438789.5 117.7 458900.3 5438789.502408
                                117.749009 458900.3 5438789.509607 117.797545 458900.3 5438789.52153
                                117.845142 458900.3 5438789.53806 117.891342 458900.3 5438789.559039
                                117.935698 458900.3 5438789.584265 117.977785 458900.3
                                5438789.613495 118.017197 458900.3 5438789.646447 118.053553
                                458900.3 5438789.682803 118.086505 458900.3 5438789.722215
                                118.115735 458900.3 5438789.764302 118.140961 458900.3
                                5438789.808658 118.16194 458900.3 5438789.854858 118.17847 458900.3
                                5438789.902455 118.190393 458900.3 5438789.950991 118.197592
                                458900.3 5438790.0 118.2 458900.3 5438790.049009 118.197592 458900.3
                                5438790.097545 118.190393 458900.3 5438790.145142 118.17847 458900.3
                                5438790.191342 118.16194 458900.3 5438790.235698 118.140961 458900.3
                                5438790.277785 118.115735 458900.3 5438790.317197 118.086505
                                458900.3 5438790.353553 118.053553 458900.3 5438790.386505
                                118.017197</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.wWxjhW73retZkAs8CSXd">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_LR.PO3ecKwLvBGe8uGChdcS">
                              <gml:posList srsDimension="3">458900.0 5438785.0 116.4 458900.0
                                5438785.0 116.9 458900.0 5438790.0 119.786751 458900.0 5438795.0
                                116.9 458900.0 5438795.0 116.4 458900.0 5438785.0
                                116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                          <gml:interior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_LR.oEgtfZeereMRzv2VnUdz">
                              <gml:posList srsDimension="3">458900.0 5438790.415735 117.977785
                                458900.0 5438790.386505 118.017197 458900.0 5438790.353553
                                118.053553 458900.0 5438790.317197 118.086505 458900.0
                                5438790.277785 118.115735 458900.0 5438790.235698 118.140961
                                458900.0 5438790.191342 118.16194 458900.0 5438790.145142 118.17847
                                458900.0 5438790.097545 118.190393 458900.0 5438790.049009
                                118.197592 458900.0 5438790.0 118.2 458900.0 5438789.950991
                                118.197592 458900.0 5438789.902455 118.190393 458900.0
                                5438789.854858 118.17847 458900.0 5438789.808658 118.16194 458900.0
                                5438789.764302 118.140961 458900.0 5438789.722215 118.115735
                                458900.0 5438789.682803 118.086505 458900.0 5438789.646447
                                118.053553 458900.0 5438789.613495 118.017197 458900.0
                                5438789.584265 117.977785 458900.0 5438789.559039 117.935698
                                458900.0 5438789.53806 117.891342 458900.0 5438789.52153 117.845142
                                458900.0 5438789.509607 117.797545 458900.0 5438789.502408
                                117.749009 458900.0 5438789.5 117.7 458900.0 5438789.502408
                                117.650991 458900.0 5438789.509607 117.602455 458900.0 5438789.52153
                                117.554858 458900.0 5438789.53806 117.508658 458900.0 5438789.559039
                                117.464302 458900.0 5438789.584265 117.422215 458900.0
                                5438789.613495 117.382803 458900.0 5438789.646447 117.346447
                                458900.0 5438789.682803 117.313495 458900.0 5438789.722215
                                117.284265 458900.0 5438789.764302 117.259039 458900.0
                                5438789.808658 117.23806 458900.0 5438789.854858 117.22153 458900.0
                                5438789.902455 117.209607 458900.0 5438789.950991 117.202408
                                458900.0 5438790.0 117.2 458900.0 5438790.049009 117.202408 458900.0
                                5438790.097545 117.209607 458900.0 5438790.145142 117.22153 458900.0
                                5438790.191342 117.23806 458900.0 5438790.235698 117.259039 458900.0
                                5438790.277785 117.284265 458900.0 5438790.317197 117.313495
                                458900.0 5438790.353553 117.346447 458900.0 5438790.386505
                                117.382803 458900.0 5438790.415735 117.422215 458900.0
                                5438790.440961 117.464302 458900.0 5438790.46194 117.508658 458900.0
                                5438790.47847 117.554858 458900.0 5438790.490393 117.602455 458900.0
                                5438790.497592 117.650991 458900.0 5438790.5 117.7 458900.0
                                5438790.497592 117.749009 458900.0 5438790.490393 117.797545
                                458900.0 5438790.47847 117.845142 458900.0 5438790.46194 117.891342
                                458900.0 5438790.440961 117.935698 458900.0 5438790.415735
                                117.977785</gml:posList>
                            </gml:LinearRing>
                          </gml:interior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.S5hjnW5f4RTmUNXhajTm">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.386505 118.017197
                                458900.0 5438790.415735 117.977785 458900.3 5438790.415735
                                117.977785 458900.3 5438790.386505 118.017197 458900.0
                                5438790.386505 118.017197</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.RYEQV8PDhrzLe6rGYu69">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.415735 117.977785
                                458900.0 5438790.440961 117.935698 458900.3 5438790.440961
                                117.935698 458900.3 5438790.415735 117.977785 458900.0
                                5438790.415735 117.977785</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.lNi8zFN1xc8zlTLCnXxb">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.440961 117.935698
                                458900.0 5438790.46194 117.891342 458900.3 5438790.46194 117.891342
                                458900.3 5438790.440961 117.935698 458900.0 5438790.440961
                                117.935698</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.9UZiJ4W3dVSChw9hSdhI">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.46194 117.891342
                                458900.0 5438790.47847 117.845142 458900.3 5438790.47847 117.845142
                                458900.3 5438790.46194 117.891342 458900.0 5438790.46194
                                117.891342</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.lCzFtw4hrU6T6gNkGeXK">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.47847 117.845142
                                458900.0 5438790.490393 117.797545 458900.3 5438790.490393
                                117.797545 458900.3 5438790.47847 117.845142 458900.0 5438790.47847
                                117.845142</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.LrzH813FWTwg49px8uZK">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.490393 117.797545
                                458900.0 5438790.497592 117.749009 458900.3 5438790.497592
                                117.749009 458900.3 5438790.490393 117.797545 458900.0
                                5438790.490393 117.797545</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.t337iQ17r02Tkh9o5jox">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.497592 117.749009
                                458900.0 5438790.5 117.7 458900.3 5438790.5 117.7 458900.3
                                5438790.497592 117.749009 458900.0 5438790.497592
                                117.749009</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.FqSnOIQmCNlbZ7EUG65P">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.5 117.7 458900.0
                                5438790.497592 117.650991 458900.3 5438790.497592 117.650991
                                458900.3 5438790.5 117.7 458900.0 5438790.5 117.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.woAg1vYaxJBPjUVLvNgX">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.497592 117.650991
                                458900.0 5438790.490393 117.602455 458900.3 5438790.490393
                                117.602455 458900.3 5438790.497592 117.650991 458900.0
                                5438790.497592 117.650991</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.1roawYgfujIWUmybzfVY">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.490393 117.602455
                                458900.0 5438790.47847 117.554858 458900.3 5438790.47847 117.554858
                                458900.3 5438790.490393 117.602455 458900.0 5438790.490393
                                117.602455</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.Is27JY3f1wMLCC07MrYf">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.47847 117.554858
                                458900.0 5438790.46194 117.508658 458900.3 5438790.46194 117.508658
                                458900.3 5438790.47847 117.554858 458900.0 5438790.47847
                                117.554858</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.5WOOxXlwkr29D71364vr">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.46194 117.508658
                                458900.0 5438790.440961 117.464302 458900.3 5438790.440961
                                117.464302 458900.3 5438790.46194 117.508658 458900.0 5438790.46194
                                117.508658</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.OBOqtpWkIsKpPIak3kWU">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.440961 117.464302
                                458900.0 5438790.415735 117.422215 458900.3 5438790.415735
                                117.422215 458900.3 5438790.440961 117.464302 458900.0
                                5438790.440961 117.464302</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.j4nXWbRdJB3vEOwx0rb0">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.415735 117.422215
                                458900.0 5438790.386505 117.382803 458900.3 5438790.386505
                                117.382803 458900.3 5438790.415735 117.422215 458900.0
                                5438790.415735 117.422215</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.xqz6S2wvc1WmnmF8TJPV">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.386505 117.382803
                                458900.0 5438790.353553 117.346447 458900.3 5438790.353553
                                117.346447 458900.3 5438790.386505 117.382803 458900.0
                                5438790.386505 117.382803</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.FrtFDmApoIOOFmWSng1T">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.353553 117.346447
                                458900.0 5438790.317197 117.313495 458900.3 5438790.317197
                                117.313495 458900.3 5438790.353553 117.346447 458900.0
                                5438790.353553 117.346447</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.HTlUzjLhhEZgA8EoxURH">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.317197 117.313495
                                458900.0 5438790.277785 117.284265 458900.3 5438790.277785
                                117.284265 458900.3 5438790.317197 117.313495 458900.0
                                5438790.317197 117.313495</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.pLCFknO9ipWFZVuh4g5s">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.277785 117.284265
                                458900.0 5438790.235698 117.259039 458900.3 5438790.235698
                                117.259039 458900.3 5438790.277785 117.284265 458900.0
                                5438790.277785 117.284265</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.EbR3oSx11uVKRsPhfVAo">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.235698 117.259039
                                458900.0 5438790.191342 117.23806 458900.3 5438790.191342 117.23806
                                458900.3 5438790.235698 117.259039 458900.0 5438790.235698
                                117.259039</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.iieDp8XsFrxDprm3YXrR">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.191342 117.23806
                                458900.0 5438790.145142 117.22153 458900.3 5438790.145142 117.22153
                                458900.3 5438790.191342 117.23806 458900.0 5438790.191342
                                117.23806</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.B8X0nUEaCjW4AyFUTI5l">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.145142 117.22153
                                458900.0 5438790.097545 117.209607 458900.3 5438790.097545
                                117.209607 458900.3 5438790.145142 117.22153 458900.0 5438790.145142
                                117.22153</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.lS5KrYBAMAxoJhQZLwsV">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.097545 117.209607
                                458900.0 5438790.049009 117.202408 458900.3 5438790.049009
                                117.202408 458900.3 5438790.097545 117.209607 458900.0
                                5438790.097545 117.209607</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.bWEg6PPxX2ioVJjzutXB">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.049009 117.202408
                                458900.0 5438790.0 117.2 458900.3 5438790.0 117.2 458900.3
                                5438790.049009 117.202408 458900.0 5438790.049009
                                117.202408</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.zPD9dJQk2mKPhEohoKNR">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.0 117.2 458900.0
                                5438789.950991 117.202408 458900.3 5438789.950991 117.202408
                                458900.3 5438790.0 117.2 458900.0 5438790.0 117.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.8GylgWKHjJ32mhqIG7sk">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.950991 117.202408
                                458900.0 5438789.902455 117.209607 458900.3 5438789.902455
                                117.209607 458900.3 5438789.950991 117.202408 458900.0
                                5438789.950991 117.202408</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.GYwo7PvXwezoJ7EnHSC3">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.902455 117.209607
                                458900.0 5438789.854858 117.22153 458900.3 5438789.854858 117.22153
                                458900.3 5438789.902455 117.209607 458900.0 5438789.902455
                                117.209607</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.bMdGYSY2nhP2zKk0GaMI">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.854858 117.22153
                                458900.0 5438789.808658 117.23806 458900.3 5438789.808658 117.23806
                                458900.3 5438789.854858 117.22153 458900.0 5438789.854858
                                117.22153</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.z1BouNhDpqt7L44vUdZI">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.808658 117.23806
                                458900.0 5438789.764302 117.259039 458900.3 5438789.764302
                                117.259039 458900.3 5438789.808658 117.23806 458900.0 5438789.808658
                                117.23806</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.xuLKaAj8WJRwemujOLQo">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.764302 117.259039
                                458900.0 5438789.722215 117.284265 458900.3 5438789.722215
                                117.284265 458900.3 5438789.764302 117.259039 458900.0
                                5438789.764302 117.259039</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.LFkbrK5JaXzL33DWpyvf">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.722215 117.284265
                                458900.0 5438789.682803 117.313495 458900.3 5438789.682803
                                117.313495 458900.3 5438789.722215 117.284265 458900.0
                                5438789.722215 117.284265</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.nK1Ziur1nFzkCdjmPmni">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.682803 117.313495
                                458900.0 5438789.646447 117.346447 458900.3 5438789.646447
                                117.346447 458900.3 5438789.682803 117.313495 458900.0
                                5438789.682803 117.313495</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.DNn1h6v9Eg3PCHvGir2c">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.646447 117.346447
                                458900.0 5438789.613495 117.382803 458900.3 5438789.613495
                                117.382803 458900.3 5438789.646447 117.346447 458900.0
                                5438789.646447 117.346447</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.iuCZmNsxIJM4yoH8zwrQ">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.613495 117.382803
                                458900.0 5438789.584265 117.422215 458900.3 5438789.584265
                                117.422215 458900.3 5438789.613495 117.382803 458900.0
                                5438789.613495 117.382803</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.rYBdvGRTXg4SuxsTcK4Q">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.584265 117.422215
                                458900.0 5438789.559039 117.464302 458900.3 5438789.559039
                                117.464302 458900.3 5438789.584265 117.422215 458900.0
                                5438789.584265 117.422215</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.g1zW7JMWvhdyvZTGNB8I">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.559039 117.464302
                                458900.0 5438789.53806 117.508658 458900.3 5438789.53806 117.508658
                                458900.3 5438789.559039 117.464302 458900.0 5438789.559039
                                117.464302</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.plNZqyrCrOmEMZSzqebB">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.53806 117.508658
                                458900.0 5438789.52153 117.554858 458900.3 5438789.52153 117.554858
                                458900.3 5438789.53806 117.508658 458900.0 5438789.53806
                                117.508658</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.kHRICSOXPh0HYikbTRRW">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.52153 117.554858
                                458900.0 5438789.509607 117.602455 458900.3 5438789.509607
                                117.602455 458900.3 5438789.52153 117.554858 458900.0 5438789.52153
                                117.554858</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.6JXZtlF2HvZilOcWLC7B">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.509607 117.602455
                                458900.0 5438789.502408 117.650991 458900.3 5438789.502408
                                117.650991 458900.3 5438789.509607 117.602455 458900.0
                                5438789.509607 117.602455</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.A7PkEeDFsbc7cc1pnzoM">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.502408 117.650991
                                458900.0 5438789.5 117.7 458900.3 5438789.5 117.7 458900.3
                                5438789.502408 117.650991 458900.0 5438789.502408
                                117.650991</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.Dh2B2Il3hOpzZ0R3yXK3">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.5 117.7 458900.0
                                5438789.502408 117.749009 458900.3 5438789.502408 117.749009
                                458900.3 5438789.5 117.7 458900.0 5438789.5 117.7</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.XWtd5xDtGAvldhO4b7iV">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.502408 117.749009
                                458900.0 5438789.509607 117.797545 458900.3 5438789.509607
                                117.797545 458900.3 5438789.502408 117.749009 458900.0
                                5438789.502408 117.749009</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.fsA97wwpxRVOh3jgQzoN">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.509607 117.797545
                                458900.0 5438789.52153 117.845142 458900.3 5438789.52153 117.845142
                                458900.3 5438789.509607 117.797545 458900.0 5438789.509607
                                117.797545</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.tJAWU8AaLYc7PT4Fe4w2">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.52153 117.845142
                                458900.0 5438789.53806 117.891342 458900.3 5438789.53806 117.891342
                                458900.3 5438789.52153 117.845142 458900.0 5438789.52153
                                117.845142</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.02adiHKX2M8am0Lw5NDY">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.53806 117.891342
                                458900.0 5438789.559039 117.935698 458900.3 5438789.559039
                                117.935698 458900.3 5438789.53806 117.891342 458900.0 5438789.53806
                                117.891342</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.80RtE0PFNi0PWWsAdD2o">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.559039 117.935698
                                458900.0 5438789.584265 117.977785 458900.3 5438789.584265
                                117.977785 458900.3 5438789.559039 117.935698 458900.0
                                5438789.559039 117.935698</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.BdxHs3b7FRTb9olheU7H">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.584265 117.977785
                                458900.0 5438789.613495 118.017197 458900.3 5438789.613495
                                118.017197 458900.3 5438789.584265 117.977785 458900.0
                                5438789.584265 117.977785</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.9znC8SMkIVXi49sgyYNm">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.613495 118.017197
                                458900.0 5438789.646447 118.053553 458900.3 5438789.646447
                                118.053553 458900.3 5438789.613495 118.017197 458900.0
                                5438789.613495 118.017197</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.t8ER9tftSyYShIvXE4UO">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.646447 118.053553
                                458900.0 5438789.682803 118.086505 458900.3 5438789.682803
                                118.086505 458900.3 5438789.646447 118.053553 458900.0
                                5438789.646447 118.053553</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.GV0TEeZyYTZ63PQyf0LB">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.682803 118.086505
                                458900.0 5438789.722215 118.115735 458900.3 5438789.722215
                                118.115735 458900.3 5438789.682803 118.086505 458900.0
                                5438789.682803 118.086505</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.lovYLrc4E8dazm8XnJ6Q">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.722215 118.115735
                                458900.0 5438789.764302 118.140961 458900.3 5438789.764302
                                118.140961 458900.3 5438789.722215 118.115735 458900.0
                                5438789.722215 118.115735</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.LZifWJX7l9715oerySwI">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.764302 118.140961
                                458900.0 5438789.808658 118.16194 458900.3 5438789.808658 118.16194
                                458900.3 5438789.764302 118.140961 458900.0 5438789.764302
                                118.140961</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.kFBez9OCnicNk4csTN7C">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.808658 118.16194
                                458900.0 5438789.854858 118.17847 458900.3 5438789.854858 118.17847
                                458900.3 5438789.808658 118.16194 458900.0 5438789.808658
                                118.16194</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.sngyi2DzU5ABBIN1JSow">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.854858 118.17847
                                458900.0 5438789.902455 118.190393 458900.3 5438789.902455
                                118.190393 458900.3 5438789.854858 118.17847 458900.0 5438789.854858
                                118.17847</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.ePeBedPTY8R8RxNnsIgo">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.902455 118.190393
                                458900.0 5438789.950991 118.197592 458900.3 5438789.950991
                                118.197592 458900.3 5438789.902455 118.190393 458900.0
                                5438789.902455 118.190393</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.BuHftk0uQsq3XvG1gxJS">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438789.950991 118.197592
                                458900.0 5438790.0 118.2 458900.3 5438790.0 118.2 458900.3
                                5438789.950991 118.197592 458900.0 5438789.950991
                                118.197592</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.D3JjIdZ8CZ5VWArZ2VNC">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.0 118.2 458900.0
                                5438790.049009 118.197592 458900.3 5438790.049009 118.197592
                                458900.3 5438790.0 118.2 458900.0 5438790.0 118.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.09fGcZ1dtDvtggyFYYMK">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.049009 118.197592
                                458900.0 5438790.097545 118.190393 458900.3 5438790.097545
                                118.190393 458900.3 5438790.049009 118.197592 458900.0
                                5438790.049009 118.197592</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.Q4igxW57I1jbX6eRUrzl">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.097545 118.190393
                                458900.0 5438790.145142 118.17847 458900.3 5438790.145142 118.17847
                                458900.3 5438790.097545 118.190393 458900.0 5438790.097545
                                118.190393</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.qEQYqSSVQ6ih7BTkSHVt">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.145142 118.17847
                                458900.0 5438790.191342 118.16194 458900.3 5438790.191342 118.16194
                                458900.3 5438790.145142 118.17847 458900.0 5438790.145142
                                118.17847</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.5GkJ2pZ35cyTlAN4N4J7">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.191342 118.16194
                                458900.0 5438790.235698 118.140961 458900.3 5438790.235698
                                118.140961 458900.3 5438790.191342 118.16194 458900.0 5438790.191342
                                118.16194</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.BDLFVNTn1QrAVlxoF9GR">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.235698 118.140961
                                458900.0 5438790.277785 118.115735 458900.3 5438790.277785
                                118.115735 458900.3 5438790.235698 118.140961 458900.0
                                5438790.235698 118.140961</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.gYjDP0kyy9JJjqh3RzWB">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.277785 118.115735
                                458900.0 5438790.317197 118.086505 458900.3 5438790.317197
                                118.086505 458900.3 5438790.277785 118.115735 458900.0
                                5438790.277785 118.115735</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.b1F3OTLWJuHSP14HsOEr">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.317197 118.086505
                                458900.0 5438790.353553 118.053553 458900.3 5438790.353553
                                118.053553 458900.3 5438790.317197 118.086505 458900.0
                                5438790.317197 118.086505</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.d7wGMMPC069n5yP6QmxC">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.0 5438790.353553 118.053553
                                458900.0 5438790.386505 118.017197 458900.3 5438790.386505
                                118.017197 458900.3 5438790.353553 118.053553 458900.0
                                5438790.353553 118.053553</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </core:lod2Solid>
              <con:isStructuralElement>true</con:isStructuralElement>
              <con:filling>
                <con:Window
                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.RwTHVpFyEUcO8zuVwtSe">
                  <gml:name>23 - Second Floor Window01 West</gml:name>
                  <core:lod2Solid>
                    <gml:Solid>
                      <gml:exterior>
                        <gml:Shell>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.902455 118.190393
                                    458900.3 5438789.854858 118.17847 458900.3 5438789.808658
                                    118.16194 458900.3 5438789.764302 118.140961 458900.3
                                    5438789.722215 118.115735 458900.3 5438789.682803 118.086505
                                    458900.3 5438789.646447 118.053553 458900.3 5438789.613495
                                    118.017197 458900.3 5438789.584265 117.977785 458900.3
                                    5438789.559039 117.935698 458900.3 5438789.53806 117.891342
                                    458900.3 5438789.52153 117.845142 458900.3 5438789.509607
                                    117.797545 458900.3 5438789.502408 117.749009 458900.3 5438789.5
                                    117.7 458900.3 5438789.502408 117.650991 458900.3 5438789.509607
                                    117.602455 458900.3 5438789.52153 117.554858 458900.3
                                    5438789.53806 117.508658 458900.3 5438789.559039 117.464302
                                    458900.3 5438789.584265 117.422215 458900.3 5438789.613495
                                    117.382803 458900.3 5438789.646447 117.346447 458900.3
                                    5438789.682803 117.313495 458900.3 5438789.722215 117.284265
                                    458900.3 5438789.764302 117.259039 458900.3 5438789.808658
                                    117.23806 458900.3 5438789.854858 117.22153 458900.3
                                    5438789.902455 117.209607 458900.3 5438789.950991 117.202408
                                    458900.3 5438790.0 117.2 458900.3 5438790.049009 117.202408
                                    458900.3 5438790.097545 117.209607 458900.3 5438790.145142
                                    117.22153 458900.3 5438790.191342 117.23806 458900.3
                                    5438790.235698 117.259039 458900.3 5438790.277785 117.284265
                                    458900.3 5438790.317197 117.313495 458900.3 5438790.354002
                                    117.346853 458900.3 5438790.386505 117.382803 458900.3
                                    5438790.415735 117.422215 458900.3 5438790.440961 117.464302
                                    458900.3 5438790.46194 117.508658 458900.3 5438790.47847
                                    117.554858 458900.3 5438790.490393 117.602455 458900.3
                                    5438790.497592 117.650991 458900.3 5438790.5 117.7 458900.3
                                    5438790.497592 117.749009 458900.3 5438790.490393 117.797545
                                    458900.3 5438790.47847 117.845142 458900.3 5438790.46194
                                    117.891342 458900.3 5438790.440961 117.935698 458900.3
                                    5438790.415735 117.977785 458900.3 5438790.386505 118.017197
                                    458900.3 5438790.353553 118.053553 458900.3 5438790.317197
                                    118.086505 458900.3 5438790.277785 118.115735 458900.3
                                    5438790.235698 118.140961 458900.3 5438790.191342 118.16194
                                    458900.3 5438790.145142 118.17847 458900.3 5438790.097545
                                    118.190393 458900.3 5438790.049009 118.197592 458900.3 5438790.0
                                    118.2 458900.3 5438789.950991 118.197592 458900.3 5438789.902455
                                    118.190393</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.613495 117.382803
                                    458900.0 5438789.613495 117.382803 458900.0 5438789.646447
                                    117.346447 458900.3 5438789.646447 117.346447 458900.3
                                    5438789.613495 117.382803</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.808658 118.16194
                                    458900.0 5438789.808658 118.16194 458900.0 5438789.764302
                                    118.140961 458900.3 5438789.764302 118.140961 458900.3
                                    5438789.808658 118.16194</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.235698 117.259039
                                    458900.0 5438790.235698 117.259039 458900.0 5438790.277785
                                    117.284265 458900.3 5438790.277785 117.284265 458900.3
                                    5438790.235698 117.259039</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.46194 117.891342
                                    458900.0 5438790.46194 117.891342 458900.0 5438790.440961
                                    117.935698 458900.3 5438790.440961 117.935698 458900.3
                                    5438790.46194 117.891342</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.490393 117.797545
                                    458900.0 5438790.490393 117.797545 458900.0 5438790.47847
                                    117.845142 458900.3 5438790.47847 117.845142 458900.3
                                    5438790.490393 117.797545</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.559039 117.935698
                                    458900.0 5438789.559039 117.935698 458900.0 5438789.53806
                                    117.891342 458900.3 5438789.53806 117.891342 458900.3
                                    5438789.559039 117.935698</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.47847 117.845142
                                    458900.0 5438790.47847 117.845142 458900.0 5438790.46194
                                    117.891342 458900.3 5438790.46194 117.891342 458900.3
                                    5438790.47847 117.845142</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.386505 118.017197
                                    458900.0 5438790.386505 118.017197 458900.0 5438790.353553
                                    118.053553 458900.3 5438790.353553 118.053553 458900.3
                                    5438790.386505 118.017197</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.317197 118.086505
                                    458900.0 5438790.317197 118.086505 458900.0 5438790.277785
                                    118.115735 458900.3 5438790.277785 118.115735 458900.3
                                    5438790.317197 118.086505</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.950991 117.202408
                                    458900.0 5438789.950991 117.202408 458900.0 5438790.0 117.2
                                    458900.3 5438790.0 117.2 458900.3 5438789.950991
                                    117.202408</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.277785 118.115735
                                    458900.0 5438790.277785 118.115735 458900.0 5438790.235698
                                    118.140961 458900.3 5438790.235698 118.140961 458900.3
                                    5438790.277785 118.115735</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.235698 118.140961
                                    458900.0 5438790.235698 118.140961 458900.0 5438790.191342
                                    118.16194 458900.3 5438790.191342 118.16194 458900.3
                                    5438790.235698 118.140961</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.191342 118.16194
                                    458900.0 5438790.191342 118.16194 458900.0 5438790.145142
                                    118.17847 458900.3 5438790.145142 118.17847 458900.3
                                    5438790.191342 118.16194</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.097545 118.190393
                                    458900.0 5438790.097545 118.190393 458900.0 5438790.049009
                                    118.197592 458900.3 5438790.049009 118.197592 458900.3
                                    5438790.097545 118.190393</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.509607 117.797545
                                    458900.0 5438789.509607 117.797545 458900.0 5438789.502408
                                    117.749009 458900.3 5438789.502408 117.749009 458900.3
                                    5438789.509607 117.797545</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.902455 118.190393
                                    458900.0 5438789.902455 118.190393 458900.0 5438789.854858
                                    118.17847 458900.3 5438789.854858 118.17847 458900.3
                                    5438789.902455 118.190393</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.049009 118.197592
                                    458900.0 5438790.049009 118.197592 458900.0 5438790.0 118.2
                                    458900.3 5438790.0 118.2 458900.3 5438790.049009
                                    118.197592</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.440961 117.935698
                                    458900.0 5438790.440961 117.935698 458900.0 5438790.415735
                                    117.977785 458900.3 5438790.415735 117.977785 458900.3
                                    5438790.440961 117.935698</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.145142 118.17847
                                    458900.0 5438790.145142 118.17847 458900.0 5438790.097545
                                    118.190393 458900.3 5438790.097545 118.190393 458900.3
                                    5438790.145142 118.17847</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.53806 117.891342
                                    458900.0 5438789.53806 117.891342 458900.0 5438789.52153
                                    117.845142 458900.3 5438789.52153 117.845142 458900.3
                                    5438789.53806 117.891342</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.0 118.2 458900.0
                                    5438790.0 118.2 458900.0 5438789.950991 118.197592 458900.3
                                    5438789.950991 118.197592 458900.3 5438790.0 118.2</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.415735 117.422215
                                    458900.0 5438790.415735 117.422215 458900.0 5438790.440961
                                    117.464302 458900.3 5438790.440961 117.464302 458900.3
                                    5438790.415735 117.422215</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.682803 118.086505
                                    458900.0 5438789.682803 118.086505 458900.0 5438789.646447
                                    118.053553 458900.3 5438789.646447 118.053553 458900.3
                                    5438789.682803 118.086505</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.415735 117.977785
                                    458900.0 5438790.415735 117.977785 458900.0 5438790.386505
                                    118.017197 458900.3 5438790.386505 118.017197 458900.3
                                    5438790.415735 117.977785</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.950991 118.197592
                                    458900.0 5438789.950991 118.197592 458900.0 5438789.902455
                                    118.190393 458900.3 5438789.902455 118.190393 458900.3
                                    5438789.950991 118.197592</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.584265 117.977785
                                    458900.0 5438789.584265 117.977785 458900.0 5438789.559039
                                    117.935698 458900.3 5438789.559039 117.935698 458900.3
                                    5438789.584265 117.977785</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.353553 118.053553
                                    458900.0 5438790.353553 118.053553 458900.0 5438790.317197
                                    118.086505 458900.3 5438790.317197 118.086505 458900.3
                                    5438790.353553 118.053553</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.646447 118.053553
                                    458900.0 5438789.646447 118.053553 458900.0 5438789.613495
                                    118.017197 458900.3 5438789.613495 118.017197 458900.3
                                    5438789.646447 118.053553</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.0 117.2 458900.0
                                    5438790.0 117.2 458900.0 5438790.049009 117.202408 458900.3
                                    5438790.049009 117.202408 458900.3 5438790.0 117.2</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.097545 117.209607
                                    458900.0 5438790.097545 117.209607 458900.0 5438790.145142
                                    117.22153 458900.3 5438790.145142 117.22153 458900.3
                                    5438790.097545 117.209607</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.764302 117.259039
                                    458900.0 5438789.764302 117.259039 458900.0 5438789.808658
                                    117.23806 458900.3 5438789.808658 117.23806 458900.3
                                    5438789.764302 117.259039</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.277785 117.284265
                                    458900.0 5438790.277785 117.284265 458900.0 5438790.317197
                                    117.313495 458900.3 5438790.317197 117.313495 458900.3
                                    5438790.277785 117.284265</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.440961 117.464302
                                    458900.0 5438790.440961 117.464302 458900.0 5438790.46194
                                    117.508658 458900.3 5438790.46194 117.508658 458900.3
                                    5438790.440961 117.464302</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.5 117.7 458900.0
                                    5438790.5 117.7 458900.0 5438790.497592 117.749009 458900.3
                                    5438790.497592 117.749009 458900.3 5438790.5 117.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.0 5438790.353553 117.346447
                                    458900.3 5438790.354002 117.346853 458900.3 5438790.317197
                                    117.313495 458900.0 5438790.317197 117.313495 458900.0
                                    5438790.353553 117.346447</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.854858 118.17847
                                    458900.0 5438789.854858 118.17847 458900.0 5438789.808658
                                    118.16194 458900.3 5438789.808658 118.16194 458900.3
                                    5438789.854858 118.17847</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.646447 117.346447
                                    458900.0 5438789.646447 117.346447 458900.0 5438789.682803
                                    117.313495 458900.3 5438789.682803 117.313495 458900.3
                                    5438789.646447 117.346447</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.902455 117.209607
                                    458900.0 5438789.902455 117.209607 458900.0 5438789.950991
                                    117.202408 458900.3 5438789.950991 117.202408 458900.3
                                    5438789.902455 117.209607</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.47847 117.554858
                                    458900.0 5438790.47847 117.554858 458900.0 5438790.490393
                                    117.602455 458900.3 5438790.490393 117.602455 458900.3
                                    5438790.47847 117.554858</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.502408 117.749009
                                    458900.0 5438789.502408 117.749009 458900.0 5438789.5 117.7
                                    458900.3 5438789.5 117.7 458900.3 5438789.502408
                                    117.749009</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.682803 117.313495
                                    458900.0 5438789.682803 117.313495 458900.0 5438789.722215
                                    117.284265 458900.3 5438789.722215 117.284265 458900.3
                                    5438789.682803 117.313495</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.191342 117.23806
                                    458900.0 5438790.191342 117.23806 458900.0 5438790.235698
                                    117.259039 458900.3 5438790.235698 117.259039 458900.3
                                    5438790.191342 117.23806</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.490393 117.602455
                                    458900.0 5438790.490393 117.602455 458900.0 5438790.497592
                                    117.650991 458900.3 5438790.497592 117.650991 458900.3
                                    5438790.490393 117.602455</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon
                              gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.RwTHVpFyEUcO8zuVwtSe_PG.TeNfI7jOWnpnUM26smeO">
                              <gml:exterior>
                                <gml:LinearRing
                                  gml:id="_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.RwTHVpFyEUcO8zuVwtSe_LR.hSU36yxw5CBRW5wFVjCW">
                                  <gml:posList srsDimension="3">458900.0 5438790.191342 118.16194
                                    458900.0 5438790.235698 118.140961 458900.0 5438790.277785
                                    118.115735 458900.0 5438790.317197 118.086505 458900.0
                                    5438790.353553 118.053553 458900.0 5438790.386505 118.017197
                                    458900.0 5438790.415735 117.977785 458900.0 5438790.440961
                                    117.935698 458900.0 5438790.46194 117.891342 458900.0
                                    5438790.47847 117.845142 458900.0 5438790.490393 117.797545
                                    458900.0 5438790.497592 117.749009 458900.0 5438790.5 117.7
                                    458900.0 5438790.497592 117.650991 458900.0 5438790.490393
                                    117.602455 458900.0 5438790.47847 117.554858 458900.0
                                    5438790.46194 117.508658 458900.0 5438790.440961 117.464302
                                    458900.0 5438790.415735 117.422215 458900.0 5438790.386505
                                    117.382803 458900.0 5438790.353553 117.346447 458900.0
                                    5438790.317197 117.313495 458900.0 5438790.277785 117.284265
                                    458900.0 5438790.235698 117.259039 458900.0 5438790.191342
                                    117.23806 458900.0 5438790.145142 117.22153 458900.0
                                    5438790.097545 117.209607 458900.0 5438790.049009 117.202408
                                    458900.0 5438790.0 117.2 458900.0 5438789.950991 117.202408
                                    458900.0 5438789.902455 117.209607 458900.0 5438789.854858
                                    117.22153 458900.0 5438789.808658 117.23806 458900.0
                                    5438789.764302 117.259039 458900.0 5438789.722215 117.284265
                                    458900.0 5438789.682803 117.313495 458900.0 5438789.646447
                                    117.346447 458900.0 5438789.613495 117.382803 458900.0
                                    5438789.584265 117.422215 458900.0 5438789.559039 117.464302
                                    458900.0 5438789.53806 117.508658 458900.0 5438789.52153
                                    117.554858 458900.0 5438789.509607 117.602455 458900.0
                                    5438789.502408 117.650991 458900.0 5438789.5 117.7 458900.0
                                    5438789.502408 117.749009 458900.0 5438789.509607 117.797545
                                    458900.0 5438789.52153 117.845142 458900.0 5438789.53806
                                    117.891342 458900.0 5438789.559039 117.935698 458900.0
                                    5438789.584265 117.977785 458900.0 5438789.613495 118.017197
                                    458900.0 5438789.646447 118.053553 458900.0 5438789.682803
                                    118.086505 458900.0 5438789.722215 118.115735 458900.0
                                    5438789.764302 118.140961 458900.0 5438789.808658 118.16194
                                    458900.0 5438789.854858 118.17847 458900.0 5438789.902455
                                    118.190393 458900.0 5438789.950991 118.197592 458900.0 5438790.0
                                    118.2 458900.0 5438790.049009 118.197592 458900.0 5438790.097545
                                    118.190393 458900.0 5438790.145142 118.17847 458900.0
                                    5438790.191342 118.16194</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.53806 117.508658
                                    458900.0 5438789.53806 117.508658 458900.0 5438789.559039
                                    117.464302 458900.3 5438789.559039 117.464302 458900.3
                                    5438789.53806 117.508658</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.509607 117.602455
                                    458900.0 5438789.509607 117.602455 458900.0 5438789.52153
                                    117.554858 458900.3 5438789.52153 117.554858 458900.3
                                    5438789.509607 117.602455</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.764302 118.140961
                                    458900.0 5438789.764302 118.140961 458900.0 5438789.722215
                                    118.115735 458900.3 5438789.722215 118.115735 458900.3
                                    5438789.764302 118.140961</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.559039 117.464302
                                    458900.0 5438789.559039 117.464302 458900.0 5438789.584265
                                    117.422215 458900.3 5438789.584265 117.422215 458900.3
                                    5438789.559039 117.464302</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.808658 117.23806
                                    458900.0 5438789.808658 117.23806 458900.0 5438789.854858
                                    117.22153 458900.3 5438789.854858 117.22153 458900.3
                                    5438789.808658 117.23806</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.613495 118.017197
                                    458900.0 5438789.613495 118.017197 458900.0 5438789.584265
                                    117.977785 458900.3 5438789.584265 117.977785 458900.3
                                    5438789.613495 118.017197</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.502408 117.650991
                                    458900.0 5438789.502408 117.650991 458900.0 5438789.509607
                                    117.602455 458900.3 5438789.509607 117.602455 458900.3
                                    5438789.502408 117.650991</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.52153 117.554858
                                    458900.0 5438789.52153 117.554858 458900.0 5438789.53806
                                    117.508658 458900.3 5438789.53806 117.508658 458900.3
                                    5438789.52153 117.554858</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.386505 117.382803
                                    458900.0 5438790.386505 117.382803 458900.0 5438790.415735
                                    117.422215 458900.3 5438790.415735 117.422215 458900.3
                                    5438790.386505 117.382803</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.722215 117.284265
                                    458900.0 5438789.722215 117.284265 458900.0 5438789.764302
                                    117.259039 458900.3 5438789.764302 117.259039 458900.3
                                    5438789.722215 117.284265</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.854858 117.22153
                                    458900.0 5438789.854858 117.22153 458900.0 5438789.902455
                                    117.209607 458900.3 5438789.902455 117.209607 458900.3
                                    5438789.854858 117.22153</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.049009 117.202408
                                    458900.0 5438790.049009 117.202408 458900.0 5438790.097545
                                    117.209607 458900.3 5438790.097545 117.209607 458900.3
                                    5438790.049009 117.202408</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.145142 117.22153
                                    458900.0 5438790.145142 117.22153 458900.0 5438790.191342
                                    117.23806 458900.3 5438790.191342 117.23806 458900.3
                                    5438790.145142 117.22153</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.584265 117.422215
                                    458900.0 5438789.584265 117.422215 458900.0 5438789.613495
                                    117.382803 458900.3 5438789.613495 117.382803 458900.3
                                    5438789.584265 117.422215</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.52153 117.845142
                                    458900.0 5438789.52153 117.845142 458900.0 5438789.509607
                                    117.797545 458900.3 5438789.509607 117.797545 458900.3
                                    5438789.52153 117.845142</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.5 117.7 458900.0
                                    5438789.5 117.7 458900.0 5438789.502408 117.650991 458900.3
                                    5438789.502408 117.650991 458900.3 5438789.5 117.7</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.46194 117.508658
                                    458900.0 5438790.46194 117.508658 458900.0 5438790.47847
                                    117.554858 458900.3 5438790.47847 117.554858 458900.3
                                    5438790.46194 117.508658</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.497592 117.650991
                                    458900.0 5438790.497592 117.650991 458900.0 5438790.5 117.7
                                    458900.3 5438790.5 117.7 458900.3 5438790.497592
                                    117.650991</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438790.497592 117.749009
                                    458900.0 5438790.497592 117.749009 458900.0 5438790.490393
                                    117.797545 458900.3 5438790.490393 117.797545 458900.3
                                    5438790.497592 117.749009</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.3 5438789.722215 118.115735
                                    458900.0 5438789.722215 118.115735 458900.0 5438789.682803
                                    118.086505 458900.3 5438789.682803 118.086505 458900.3
                                    5438789.722215 118.115735</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                          <gml:surfaceMember>
                            <gml:Polygon>
                              <gml:exterior>
                                <gml:LinearRing>
                                  <gml:posList srsDimension="3">458900.0 5438790.353553 117.346447
                                    458900.0 5438790.386505 117.382803 458900.3 5438790.386505
                                    117.382803 458900.3 5438790.354002 117.346853 458900.0
                                    5438790.353553 117.346447</gml:posList>
                                </gml:LinearRing>
                              </gml:exterior>
                            </gml:Polygon>
                          </gml:surfaceMember>
                        </gml:Shell>
                      </gml:exterior>
                    </gml:Solid>
                  </core:lod2Solid>
                  <con:class>Window</con:class>
                </con:Window>
              </con:filling>
              <bldg:class>Wall</bldg:class>
            </bldg:BuildingConstructiveElement>
          </bldg:buildingConstructiveElement>
          <bldg:buildingConstructiveElement>
            <bldg:BuildingConstructiveElement
              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi">
              <gml:name>11 - Second Floor Roof South</gml:name>
              <core:lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_PG.1MV05AI6uNdePdx4fxAn">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_LR.PjRerCviIUTzOVJxCNyw">
                              <gml:posList srsDimension="3">458912.5 5438790.0 120.017691 458912.5
                                5438790.0 119.786751 458899.5 5438790.0 119.786751 458899.5
                                5438790.0 120.017691 458912.5 5438790.0 120.017691</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_PG.9bUEvk7j5tVIPNlVW8uJ">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_LR.214TSZ9XYDFJXNHLgNHZ">
                              <gml:posList srsDimension="3">458912.5 5438784.5 116.842265 458912.5
                                5438784.5 116.611325 458912.5 5438790.0 119.786751 458912.5
                                5438790.0 120.017691 458912.5 5438784.5 116.842265</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_PG.aQ3tfZHgKl9ecYAN5Ioo">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_LR.3kb3LCU9DvfrQhMIerrl">
                              <gml:posList srsDimension="3">458899.5 5438784.5 116.842265 458899.5
                                5438784.5 116.611325 458912.5 5438784.5 116.611325 458912.5
                                5438784.5 116.842265 458899.5 5438784.5 116.842265</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_PG.eBexp5vGMTPuTswk1Lqa">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_LR.1hufme0bUZmffF5fVafq">
                              <gml:posList srsDimension="3">458899.5 5438790.0 120.017691 458899.5
                                5438790.0 119.786751 458899.5 5438784.5 116.611325 458899.5
                                5438784.5 116.842265 458899.5 5438790.0 120.017691</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_PG.llAA4hqdggjuq9LXMqqe">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_LR.Ov6mkIKl1wlzqUr7dYpr">
                              <gml:posList srsDimension="3">458912.5 5438784.5 116.611325 458899.5
                                5438784.5 116.611325 458899.5 5438790.0 119.786751 458912.5
                                5438790.0 119.786751 458912.5 5438784.5 116.611325</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_PG.V3ha3sDA4z9ACdq9OhrW">
                          <gml:exterior>
                            <gml:LinearRing
                              gml:id="_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_LR.G1Is6jtBzZa5hiCOFxqu">
                              <gml:posList srsDimension="3">458899.5 5438784.5 116.842265 458912.5
                                5438784.5 116.842265 458912.5 5438790.0 120.017691 458899.5
                                5438790.0 120.017691 458899.5 5438784.5 116.842265</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </core:lod2Solid>
              <con:isStructuralElement>true</con:isStructuralElement>
              <bldg:class>Roof</bldg:class>
            </bldg:BuildingConstructiveElement>
          </bldg:buildingConstructiveElement>
          <bldg:buildingConstructiveElement>
            <bldg:BuildingConstructiveElement
              gml:id="_Construstruction-Inner-Walls-Openings_BD.Bd2v6nBBghEwrOLuMRpO">
              <gml:name>12 - Second Floor Floor Slab Interior</gml:name>
              <core:lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.Bd2v6nBBghEwrOLuMRpO_PG.Au8s79L1OzNGg3DYcb1i">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438789.01 116.2 458907.440173
                                5438789.009984 116.2 458907.44001 5438785.3 116.2 458900.3 5438785.3
                                116.2 458900.3 5438794.7 116.2 458911.7 5438794.7 116.2 458911.7
                                5438789.01 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.Bd2v6nBBghEwrOLuMRpO_PG.tkFsuKNUmgfely84Z0id">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438785.3 116.4 458907.44001
                                5438785.3 116.4 458907.440173 5438789.009984 116.4 458911.7
                                5438789.01 116.4 458911.7 5438794.7 116.4 458900.3 5438794.7 116.4
                                458900.3 5438785.3 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.Bd2v6nBBghEwrOLuMRpO_PG.1oIln8w50rEyFGmWQGda">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458907.440173 5438789.009984 116.2
                                458907.440173 5438789.009984 116.4 458907.44001 5438785.3 116.4
                                458907.44001 5438785.3 116.2 458907.440173 5438789.009984
                                116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.Bd2v6nBBghEwrOLuMRpO_PG.lkEXqAsPGgzYYpSISIuY">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438789.01 116.2 458911.7
                                5438789.01 116.4 458907.440173 5438789.009984 116.4 458907.440173
                                5438789.009984 116.2 458911.7 5438789.01 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.Bd2v6nBBghEwrOLuMRpO_PG.di297lmDY2x3chLBO7lY">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458911.7 5438794.7 116.2 458911.7
                                5438794.7 116.4 458911.7 5438789.01 116.4 458911.7 5438789.01 116.2
                                458911.7 5438794.7 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.Bd2v6nBBghEwrOLuMRpO_PG.vEPjFMb5Bfk4n6lFDwdY">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438794.7 116.2 458900.3
                                5438794.7 116.4 458911.7 5438794.7 116.4 458911.7 5438794.7 116.2
                                458900.3 5438794.7 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.Bd2v6nBBghEwrOLuMRpO_PG.vYKxuio9jeY5YBX5FuoX">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438785.3 116.2 458900.3
                                5438785.3 116.4 458900.3 5438794.7 116.4 458900.3 5438794.7 116.2
                                458900.3 5438785.3 116.2</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon
                          gml:id="_Construstruction-Inner-Walls-Openings_BD.Bd2v6nBBghEwrOLuMRpO_PG.QZc36E47EpExUHOOe3Pp">
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension="3">458900.3 5438785.3 116.4 458900.3
                                5438785.3 116.2 458907.44001 5438785.3 116.2 458907.44001 5438785.3
                                116.4 458900.3 5438785.3 116.4</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </core:lod2Solid>
              <con:isStructuralElement>true</con:isStructuralElement>
              <bldg:class>Slab</bldg:class>
            </bldg:BuildingConstructiveElement>
          </bldg:buildingConstructiveElement>
        </bldg:Storey>
      </bldg:buildingSubdivision>
    </bldg:Building>
  </core:cityObjectMember>
  <core:appearanceMember>
    <app:Appearance gml:id="ID_ef2cc176-b404-3b57-8cd7-0ac1d8f81af7">
      <app:surfaceData>
        <app:ParameterizedTexture>
          <app:imageURI>textures/FZK-Haus-Back.png</app:imageURI>
          <app:wrapMode>wrap</app:wrapMode>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_PG.e9AMeV0pEURTngbpCIid</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>4.812742796881746E-16 6.106226635438361E-16
                    4.812742796881746E-16 0.055082762670476876 -0.9999999999999998
                    0.055082762670476876 -0.9999999999999998 6.106226635438361E-16
                    4.812742796881746E-16 6.106226635438361E-16</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_LR.1wtpWcM1ybr7En9jkc48</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.GhhgkoiACRoutZj6gPJD</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>-0.9999999999999997 0.7987000537971238 -0.9999999999999997
                    0.05508275569370144 5.113539221686852E-16 0.05508275569370144
                    5.113539221686852E-16 0.7987000537971238 -0.9999999999999997
                    0.7987000537971238</app:textureCoordinates>
                  <app:textureCoordinates>-0.7329166659190912 0.2754138094340573 -0.8995833324157578
                    0.2754138094340573 -0.8995833324157578 0.6059103801950257 -0.7329166659190912
                    0.6059103801950257 -0.7329166659190912
                    0.2754138094340573</app:textureCoordinates>
                  <app:textureCoordinates>-0.38833333293723293 0.2754138094340573
                    -0.5549999994338995 0.2754138094340573 -0.5549999994338995 0.6059103801950257
                    -0.38833333293723293 0.6059103801950257 -0.38833333293723293
                    0.2754138094340573</app:textureCoordinates>
                  <app:textureCoordinates>-0.0874999999107495 0.2754138094340573 -0.2541666664074162
                    0.2754138094340573 -0.2541666664074162 0.6059103801950257 -0.0874999999107495
                    0.6059103801950257 -0.0874999999107495
                    0.2754138094340573</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_LR.rJ8039v7rlqStEtLP060</app:ring>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_LR.qYUpaoqvi5HuqJtc70xY</app:ring>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_LR.BEQS7EgIBnVnvbagopYh</app:ring>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_LR.fm520RqpNLcjtkZnu7G7</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_PG.6s7V4a1OB8u1aTStTcbJ</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>-4.967048506721028E-10 0.7987000565293122
                    -4.967048506721028E-10 0.9364069611535101 -1.0000000004967051 0.9364069611535101
                    -1.0000000004967051 0.7987000565293122 -4.967048506721028E-10
                    0.7987000565293122</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_LR.ojQ6g83dDnYM4v1IhtAg</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.Wi0ORs5kGMnKQlfhDaYi_PG.TOVTlyvimFvgR5oiaBXV</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>-0.899583333333333 0.2754138030924179 -0.7329166666666662
                    0.2754138030924179 -0.7329166666666662 0.6059103873232469 -0.899583333333333
                    0.6059103873232469 -0.899583333333333
                    0.2754138030924179</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.Wi0ORs5kGMnKQlfhDaYi_LR.0eYV408FAjRuy4cttZmh</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.4hdRTFC3hEyX9Ur6AK11_PG.QxXXZUcYDSPgAvfml3o9</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>-0.25416666666666615 0.275413803092418
                    -0.08749999999999945 0.275413803092418 -0.08749999999999945 0.6059103873232466
                    -0.25416666666666615 0.6059103873232466 -0.25416666666666615
                    0.275413803092418</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.4hdRTFC3hEyX9Ur6AK11_LR.poSQunJA2uWxlLFqMgdz</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.BrpRZ0nUpEXSyByeHjSs_PG.JGb8xPG9HlFIsgBWPU4U</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>-0.5549999999999995 0.275413803092418 -0.3883333333333327
                    0.275413803092418 -0.3883333333333327 0.6059103873232466 -0.5549999999999995
                    0.6059103873232466 -0.5549999999999995
                    0.275413803092418</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.BrpRZ0nUpEXSyByeHjSs_LR.xkPmtBFpsnKTartUJOsW</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
        </app:ParameterizedTexture>
      </app:surfaceData>
      <app:surfaceData>
        <app:ParameterizedTexture>
          <app:imageURI>textures/FZK-Haus-Right.png</app:imageURI>
          <app:wrapMode>wrap</app:wrapMode>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_PG.hNmG4YmoXQMBm8b42JJ4</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>1.0 -2.914335439641036E-16 1.0 0.030685671783026273 0.0
                    0.030685671783026273 0.0 -2.914335439641036E-16 1.0
                    -2.914335439641036E-16</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_LR.8mE1jXWCpsO6DUwaB6i7</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.vPkHyW4ZqK4NBbln6BPU</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>0.0 0.44494223811037215 0.0 0.030685667896383145 1.0
                    0.030685667896383145 1.0 0.44494223811037215 0.0
                    0.44494223811037215</app:textureCoordinates>
                  <app:textureCoordinates>0.32049999967309 0.1534283567323004 0.12049999987709002
                    0.1534283567323004 0.12049999987709002 0.33754238449915064 0.32049999967309
                    0.33754238449915064 0.32049999967309 0.1534283567323004</app:textureCoordinates>
                  <app:textureCoordinates>0.850239399132756 0.1534283567323004 0.6502393993367559
                    0.1534283567323004 0.6502393993367559 0.33754238449915064 0.850239399132756
                    0.33754238449915064 0.850239399132756
                    0.1534283567323004</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_LR.LgPfu2laSzYqIXLAF7BV</app:ring>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_LR.AGuJLjkgatzZDk21NVwj</app:ring>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_LR.RvQaGjIjyCTOYZmGhbt8</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.oGvYxDaN7tEMUBruq989</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>1.1999999987760002 1.028337296110234 1.1999999987760002
                    1.3351940090549845 1.169999999403954 1.3351940090549845 1.169999999403954
                    1.028337296110234 1.1999999987760002 1.028337296110234</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_LR.JHgH5G87cusRnbQpajza</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.aaC58mJm7tRYJrf71O1t</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>1.1999999987760002 0.1534283567323004 1.1999999987760002
                    0.33754238449915064 1.169999999403954 0.33754238449915064 1.169999999403954
                    0.1534283567323004 1.1999999987760002
                    0.1534283567323004</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_LR.rbP3MGxybQWYJ7opJa9n</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.A5iro2UuhcRvA0U5UnAX</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>-1.1999999987760002 1.3351940090549845 -1.1999999987760002
                    1.028337296110234 -1.169999999403954 1.028337296110234 -1.169999999403954
                    1.3351940090549845 -1.1999999987760002
                    1.3351940090549845</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_LR.TXCGVauXlyCDP9k0qMoL</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.1p4KTXynAoyl6e166LeS</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>-1.1999999987760002 0.33754238449915064
                    -1.1999999987760002 0.1534283567323004 -1.169999999403954 0.1534283567323004
                    -1.169999999403954 0.33754238449915064 -1.1999999987760002
                    0.33754238449915064</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_LR.zuGJ76CqDa57IST5SFYT</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.KcjNlHb2379iNGJW8tBO</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>1.1999999987760002 0.1534283567323004 1.1999999987760002
                    0.33754238449915064 1.1699999994039536 0.33754238449915064 1.1699999994039536
                    0.1534283567323004 1.1999999987760002
                    0.1534283567323004</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_LR.FjUf4zY9eRnPtN43qKXo</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.wTrfNM4Oxh3XEeBTCyf9</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>-1.1999999987760002 0.5224235540483627 -1.1999999987760002
                    0.21556684110361238 -1.1699999994039536 0.21556684110361238 -1.1699999994039536
                    0.5224235540483627 -1.1999999987760002
                    0.5224235540483627</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_LR.3yDBa9Gz2I1KaDiLcUBV</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.gEUqSoYeOFLY26aPvwVa</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>1.0 0.44494222539546296 1.0 0.5216564037098991
                    0.5000000000000896 0.964565929055548 -8.881784197001253E-17 0.5216564037098991
                    -8.881784197001253E-17 0.44494222539546296 1.0
                    0.44494222539546296</app:textureCoordinates>
                  <app:textureCoordinates>0.49509909949499903 0.7207438163110601 0.49999999949
                    0.7211132717934456 0.5049008994850012 0.7207438163110601 0.5097544994800505
                    0.7196392855728155 0.5145141994751955 0.7178099592785953 0.5191341994704831
                    0.715273788546107 0.5235697994659588 0.7120550150556729 0.5277784994616659
                    0.7081846313353009 0.531719699457646 0.7036999204756132 0.5353552994539376
                    0.6986441492731356 0.5386504994505765 0.6930661079452259 0.541573499447595
                    0.6870191895599367 0.544096099445022 0.6805618503210838 0.5461939994428822
                    0.6737563821413951 0.5478469994411961 0.6666679920723715 0.54903929943998
                    0.6593652625893558 0.5497591994392457 0.6519184638796126 0.549999999439
                    0.6443990935572579 0.5497591994392457 0.6368797232349033 0.54903929943998
                    0.6294329245251601 0.5478469994411961 0.6221301950421444 0.5461939994428822
                    0.6150418049731207 0.544096099445022 0.608236336793432 0.541573499447595
                    0.6017789975545791 0.5386504994505765 0.5957320791692899 0.5353552994539376
                    0.5901540378413802 0.531719699457646 0.5850982666389025 0.5277784994616659
                    0.580613555779215 0.5235697994659588 0.5767431720588428 0.5191341994704831
                    0.5735243985684089 0.5145141994751955 0.5709882278359206 0.5097544994800505
                    0.5691589015417003 0.5049008994850012 0.5680543708034558 0.49999999949
                    0.5676849153210702 0.49509909949499903 0.5680543708034558 0.4902454994999496
                    0.5691589015417003 0.4854857995048046 0.5709882278359206 0.48086579950951697
                    0.5735243985684089 0.4764301995140412 0.5767431720588428 0.4722214995183341
                    0.580613555779215 0.46828029952235406 0.5850982666389025 0.46464469952606247
                    0.5901540378413802 0.46134949952942356 0.5957320791692899 0.45842649953240505
                    0.6017789975545791 0.45590389953497806 0.608236336793432 0.45380599953711787
                    0.6150418049731207 0.4520481995389109 0.622771832428912 0.45096069954002016
                    0.6294329245251601 0.45024079954075447 0.6368797232349033 0.44999999954100006
                    0.6443990935572579 0.45024079954075447 0.6519184638796126 0.45096069954002016
                    0.6593652625893558 0.45215299953880406 0.6666679920723715 0.45380599953711787
                    0.6737563821413951 0.45590389953497806 0.6805618503210838 0.45842649953240505
                    0.6870191895599367 0.46134949952942356 0.6930661079452259 0.46464469952606247
                    0.6986441492731356 0.46828029952235406 0.7036999204756132 0.4722214995183341
                    0.7081846313353009 0.4764301995140412 0.7120550150556729 0.48086579950951697
                    0.715273788546107 0.4854857995048046 0.7178099592785953 0.4902454994999496
                    0.7196392855728155 0.49509909949499903
                    0.7207438163110601</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_LR.BME13xGiI9U3Wt204amO</app:ring>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_LR.iDrepQ9hvt1LcTm6hJYG</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.xScpPtAxLzHxzuP1YU86_PG.Ts4Xm94yf5sdqEh6DGPh</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>0.12050000000000005 0.15342835319948087 0.3205000000000001
                    0.15342835319948087 0.3205000000000001 0.33754238847016166 0.12050000000000005
                    0.33754238847016166 0.12050000000000005
                    0.15342835319948087</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.xScpPtAxLzHxzuP1YU86_LR.VJX63X8ytoACnOWVhI5H</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.1j3CFxYaBLINTZb5QAjF_PG.clckEsEN2ccOxgWjKQwZ</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>0.5353555595477273 0.6986436785772794 0.5317199837382072
                    0.7036994054891696 0.5277788051963197 0.7081840770609878 0.5235701237150453
                    0.7120544268752433 0.5191345391159944 0.7152731721679281 0.5145145512508764
                    0.7178093206825416 0.5097548600037014 0.7196386309511282 0.5049012652885784
                    0.7207431520132398 0.5000003670563216 0.7211126042590468 0.49509946528857834
                    0.7207431520132398 0.49024586000370135 0.7196386309511282 0.4854861512508764
                    0.7178093206825416 0.48086613911599446 0.7152731721679281 0.4764305237150452
                    0.7120544268752433 0.4722218051963197 0.7081840770609878 0.4682805837382072
                    0.7036994054891696 0.4646449595477274 0.6986436785772794 0.4613497328583281
                    0.6930656861152534 0.4584267039254805 0.6870188207033991 0.45590407302888175
                    0.680561538033433 0.45380614046658124 0.6737561294723804 0.4521531065505772
                    0.6666678015005022 0.45096077160901776 0.6593651359923315 0.4502408359781264
                    0.6519184025195375 0.4499999999999999 0.6443990980698886 0.45024076402187335
                    0.6368797936202397 0.4509606283909821 0.6294330601474457 0.4520480965194817
                    0.6227720264050411 0.4538058595334184 0.6150420666673967 0.4559037269711181
                    0.6082366581063442 0.4584262960745192 0.6017793754363779 0.46134926714167174
                    0.5957325100245238 0.46464444045227254 0.5901545175624977 0.46828001626179266
                    0.5850987906506074 0.47222119480368 0.5806141190787892 0.4764298762849544
                    0.5767437692645337 0.48086546088400545 0.5735250239718491 0.4854854487491234
                    0.5709888754572355 0.4902451399962982 0.5691595651886489 0.49509873471142135
                    0.5680550441265374 0.49999963294367805 0.5676855918807304 0.5049005347114214
                    0.5680550441265374 0.5097541399962983 0.5691595651886489 0.5145138487491234
                    0.5709888754572355 0.5191338608840054 0.5735250239718491 0.5235694762849545
                    0.5767437692645337 0.52777819480368 0.5806141190787892 0.5317194162617926
                    0.5850987906506074 0.5353550404522724 0.5901545175624977 0.5386502671416716
                    0.5957325100245238 0.5415732960745191 0.6017793754363779 0.544095926971118
                    0.6082366581063442 0.5461938595334185 0.6150420666673967 0.5478468934494225
                    0.622130394639275 0.5490392283909821 0.6294330601474457 0.5497591640218733
                    0.6368797936202397 0.5499999999999999 0.6443990980698886 0.5497592359781264
                    0.6519184025195375 0.5490393716090177 0.6593651359923315 0.5478471065505771
                    0.6666678015005022 0.5461941404665813 0.6737561294723804 0.5440962730288816
                    0.680561538033433 0.5415737039254804 0.6870188207033991 0.538650732858328
                    0.6930656861152534 0.5353555595477273
                    0.6986436785772794</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.1j3CFxYaBLINTZb5QAjF_LR.fVLFGc1zHqrJPkxisCO1</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.kYrOrTm2uRtVnUR7dmUA_PG.2DZe7GT9Oiq63oxvYXH8</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>0.65023937 0.15342835319948087 0.8502393699999998
                    0.15342835319948087 0.8502393699999998 0.33754238847016166 0.65023937
                    0.33754238847016166 0.65023937 0.15342835319948087</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.kYrOrTm2uRtVnUR7dmUA_LR.wjN5SupLrHejqQJu7DZ5</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
        </app:ParameterizedTexture>
      </app:surfaceData>
      <app:surfaceData>
        <app:ParameterizedTexture>
          <app:imageURI>textures/FZK-Haus-Front.png</app:imageURI>
          <app:wrapMode>wrap</app:wrapMode>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_PG.vgpO7agF1kI7rJRF6jCg</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>1.0 -6.938893903907228E-18 1.0 0.05508276267047626
                    -1.2031856992204364E-16 0.05508276267047626 -1.2031856992204364E-16
                    -6.938893903907228E-18 1.0 -6.938893903907228E-18</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_LR.N0N0IsKBdvpy39boJBww</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.Ak1NLFqBgU5p93bMXwFH</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>2.437871641442668E-28 0.05508275569370082
                    0.416249999575425 0.0550827622600777 0.416249999575425 0.7091905585578276
                    0.5837499994045751 0.7091905585578276 0.5837499994045751 0.0550827622600777
                    1.0000000000000002 0.05508275569370082 1.0000000000000002 0.7987000537971232
                    2.437871641442668E-28 0.7987000537971232 2.437871641442668E-28
                    0.05508275569370082</app:textureCoordinates>
                  <app:textureCoordinates>0.14916666651451668 0.2754138094340567 0.14916666651451668
                    0.6059103801950251 0.3158333330111834 0.6059103801950251 0.3158333330111834
                    0.2754138094340567 0.14916666651451668
                    0.2754138094340567</app:textureCoordinates>
                  <app:textureCoordinates>0.8508333324654835 0.2754138094340567 0.6841666659688169
                    0.2754138094340567 0.6841666659688169 0.6059103801950251 0.8508333324654835
                    0.6059103801950251 0.8508333324654835
                    0.2754138094340567</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_LR.ZdDKAMpD2ZrKtevMUejU</app:ring>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_LR.Bwq4RdOfRlTfgYvYKJ5B</app:ring>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_LR.hKG6EV1RLY9KdvhmzAEm</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_PG.2dKXmAy0meKvCww51jj9</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>1.0000000000000002 0.798700040682076 1.0000000000000002
                    0.9364069453062739 8.964432033456787E-26 0.9364069453062739
                    8.964432033456787E-26 0.798700040682076 1.0000000000000002
                    0.798700040682076</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_LR.0sdBO8XZL209jw1TNaGt</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.jalS9iFDeTazxLHKmvaT_PG.2Y9MQFrdNWo9l0wVSvOe</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>0.4162500003973645 0.055082762465276956 0.583749999602636
                    0.05508276246527696 0.5837499996026358 0.7091905592250175 0.41625000039736426
                    0.7091905592250175 0.4162500003973645
                    0.055082762465276956</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.jalS9iFDeTazxLHKmvaT_LR.4oj9q66rJOIpS7IyvZh4</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.9aFq0L7vXwXHZHTBaShi_PG.5zDET0PYEarac0QrwsrW</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>0.14916666666666667 0.27541380309241736
                    0.31583333333333335 0.27541380309241736 0.31583333333333335 0.6059103873232462
                    0.14916666666666667 0.6059103873232462 0.14916666666666667
                    0.27541380309241736</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.9aFq0L7vXwXHZHTBaShi_LR.p0evYWdChScHiKesrLSv</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.Wihqw5MOkP7pIbGLXREi_PG.kAv2fdFy0RBKKQ63mOXW</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>0.6841666666666666 0.2754138030924173 0.8508333333333332
                    0.2754138030924173 0.8508333333333332 0.6059103873232462 0.6841666666666666
                    0.6059103873232462 0.6841666666666666
                    0.2754138030924173</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.Wihqw5MOkP7pIbGLXREi_LR.0OimShpXKYJ3dvJFZjVR</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
        </app:ParameterizedTexture>
      </app:surfaceData>
      <app:surfaceData>
        <app:ParameterizedTexture>
          <app:imageURI>textures/FZK-Haus-Left.png</app:imageURI>
          <app:wrapMode>wrap</app:wrapMode>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_PG.MgxBTndXeCqtGtBjgXrT</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>5.775291356258095E-16 0.0 5.775291356258095E-16
                    0.03068567178302657 -0.9999999999999994 0.03068567178302657 -0.9999999999999994
                    0.0 5.775291356258095E-16 0.0</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_LR.fGwcpAcL6rIhCv6OIXnh</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.pT57K3pbUX6MaTHCDERp</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>-0.9999999999999994 0.03068566789638344
                    -0.5504999994384895 0.030685671554400502 -0.5504999994384895 0.33907666806387465
                    -0.4494999995415095 0.33907666806387465 -0.4494999995415095 0.030685671554400502
                    5.775291356254581E-16 0.03068566789638344 5.775291356254581E-16
                    0.4449422381103724 -0.9999999999999994 0.4449422381103724 -0.9999999999999994
                    0.03068566789638344</app:textureCoordinates>
                  <app:textureCoordinates>-0.6494999993375095 0.1534283567323007 -0.8494999991335095
                    0.1534283567323007 -0.8494999991335095 0.33754238449915097 -0.6494999993375095
                    0.33754238449915097 -0.6494999993375095
                    0.1534283567323007</app:textureCoordinates>
                  <app:textureCoordinates>-0.12049999987708944 0.1534283567323007
                    -0.32049999967308945 0.1534283567323007 -0.32049999967308945 0.33754238449915097
                    -0.12049999987708944 0.33754238449915097 -0.12049999987708944
                    0.1534283567323007</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_LR.JGT7zuqwhdECH8z2rvYG</app:ring>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_LR.cjhu9mKqlxqYDRjuXqYj</app:ring>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_LR.Y2HHH04DDGLJZx5evjWF</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.wWxjhW73retZkAs8CSXd</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>4.887112936773116E-16 0.4449422253955035
                    4.887112936773116E-16 0.5216564037099396 -0.5000000000000006 0.9645659290555887
                    -0.9999999999999994 0.5216564037099396 -0.9999999999999994 0.4449422253955035
                    4.887112936773116E-16 0.4449422253955035</app:textureCoordinates>
                  <app:textureCoordinates>-0.5415734994475945 0.6870191895599371 -0.538650499450576
                    0.6930661079452265 -0.535355299453937 0.6986441492731361 -0.5317196994576454
                    0.7036999204756138 -0.5277784994616653 0.7081846313353014 -0.5235697994659583
                    0.7120550150556735 -0.5191341994704826 0.7152737885461075 -0.5145141994751949
                    0.7178099592785958 -0.5097544994800499 0.719639285572816 -0.5049008994850006
                    0.7207438163110607 -0.49999999948999946 0.7211132717934461 -0.4950990994949985
                    0.7207438163110607 -0.49024549949994906 0.719639285572816 -0.485485799504804
                    0.7178099592785958 -0.4808657995095164 0.7152737885461075 -0.47643019951404064
                    0.7120550150556735 -0.47222149951833353 0.7081846313353014 -0.4682802995223535
                    0.7036999204756138 -0.4646446995260619 0.6986441492731361 -0.461349499529423
                    0.6930661079452265 -0.4584264995324045 0.6870191895599371 -0.4559038995349775
                    0.6805618503210844 -0.4538059995371173 0.6737563821413955 -0.4521529995388035
                    0.6666679920723719 -0.4509606995400196 0.6593652625893562 -0.4502407995407539
                    0.651918463879613 -0.4499999995409995 0.6443990935572584 -0.4502407995407539
                    0.6368797232349038 -0.4509606995400196 0.6294329245251606 -0.4521529995388035
                    0.622130195042145 -0.4538059995371173 0.6150418049731212 -0.4559038995349775
                    0.6082363367934325 -0.4584264995324045 0.6017789975545796 -0.461349499529423
                    0.5957320791692904 -0.4646446995260619 0.5901540378413807 -0.4682802995223535
                    0.585098266638903 -0.47222149951833353 0.5806135557792156 -0.47643019951404064
                    0.5767431720588433 -0.4808657995095164 0.5735243985684094 -0.485485799504804
                    0.5709882278359211 -0.49024549949994906 0.5691589015417009 -0.4950990994949985
                    0.5680543708034562 -0.49999999948999946 0.5676849153210708 -0.5049008994850006
                    0.5680543708034562 -0.5097544994800499 0.5691589015417009 -0.5145141994751949
                    0.5709882278359211 -0.5191341994704826 0.5735243985684094 -0.5235697994659583
                    0.5767431720588433 -0.5277784994616653 0.5806135557792156 -0.5317196994576454
                    0.585098266638903 -0.535355299453937 0.5901540378413807 -0.538650499450576
                    0.5957320791692904 -0.5415734994475945 0.6017789975545796 -0.5440960994450215
                    0.6082363367934325 -0.5461939994428816 0.6150418049731212 -0.5478469994411955
                    0.622130195042145 -0.5490392994399794 0.6294329245251606 -0.5497591994392451
                    0.6368797232349038 -0.5499999994389995 0.6443990935572584 -0.5497591994392451
                    0.651918463879613 -0.5490392994399794 0.6593652625893562 -0.5478469994411955
                    0.6666679920723719 -0.5461939994428816 0.6737563821413955 -0.5440960994450215
                    0.6805618503210844 -0.5415734994475945
                    0.6870191895599371</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_LR.PO3ecKwLvBGe8uGChdcS</app:ring>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_LR.oEgtfZeereMRzv2VnUdz</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.Rw7n0cJgxfN3IozXPOgX_PG.1LuWrQuylhqL07NV4rfH</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>-0.6494999999999996 0.1534283531994811 -0.6494999999999996
                    0.3375423884701617 -0.8494999999999995 0.3375423884701617 -0.8494999999999997
                    0.1534283531994811 -0.6494999999999996
                    0.1534283531994811</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.Rw7n0cJgxfN3IozXPOgX_LR.J5NSMaSOrDg8DhLvW3q5</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.OZzJ0PyiUVwgxGghWLkd_PG.MeDGx6kKAKC0FGVtIi5b</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>-0.12049999999999944 0.1534283531994811
                    -0.12049999999999945 0.3375423884701617 -0.32049999999999923 0.3375423884701617
                    -0.3204999999999994 0.1534283531994811 -0.12049999999999944
                    0.1534283531994811</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.OZzJ0PyiUVwgxGghWLkd_LR.oE2fLm99BAZXCqLfR1Hu</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.vTExwGEkNkFYB3tAnTrl_PG.OiuqA95bz0nXwSZHl3Dj</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>-0.5504999995231623 0.030685671780648932
                    -0.4495000004768365 0.030685672034515235 -0.4495000004768366 0.33907666764683025
                    -0.5504999995231623 0.33907666764683025 -0.5504999995231623
                    0.030685671780648932</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.vTExwGEkNkFYB3tAnTrl_LR.CefnAcQCtIPEZDGHunE4</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.RwTHVpFyEUcO8zuVwtSe_PG.TeNfI7jOWnpnUM26smeO</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>-0.5191338608840059 0.7152731721679295 -0.523569476284955
                    0.7120544268752448 -0.5277781948036805 0.7081840770609893 -0.5317194162617932
                    0.7036994054891711 -0.535355040452273 0.6986436785772808 -0.5386502671416722
                    0.6930656861152549 -0.5415732960745197 0.6870188207034006 -0.5440959269711185
                    0.6805615380334344 -0.546193859533419 0.6737561294723817 -0.5478468934494231
                    0.6666678015005035 -0.5490392283909826 0.6593651359923328 -0.5497591640218739
                    0.6519184025195388 -0.5500000000000005 0.6443990980698899 -0.549759235978127
                    0.636879793620241 -0.5490393716090183 0.629433060147447 -0.5478471065505777
                    0.6221303946392763 -0.546194140466582 0.615042066667398 -0.5440962730288823
                    0.6082366581063454 -0.541573703925481 0.6017793754363793 -0.5386507328583285
                    0.5957325100245251 -0.5353555595477278 0.5901545175624989 -0.5317199837382077
                    0.5850987906506087 -0.5277788051963203 0.5806141190787905 -0.5235701237150457
                    0.5767437692645351 -0.5191345391159949 0.5735250239718503 -0.5145145512508769
                    0.5709888754572369 -0.509754860003702 0.5691595651886502 -0.5049012652885789
                    0.5680550441265386 -0.5000003670563221 0.5676855918807316 -0.4950994652885788
                    0.5680550441265386 -0.4902458600037018 0.5691595651886502 -0.48548615125087685
                    0.5709888754572369 -0.4808661391159948 0.5735250239718503 -0.47643052371504563
                    0.5767437692645351 -0.47222180519632023 0.5806141190787905 -0.4682805837382075
                    0.5850987906506087 -0.4646449595477277 0.5901545175624989 -0.4613497328583284
                    0.5957325100245251 -0.45842670392548085 0.6017793754363793 -0.4559040730288822
                    0.6082366581063454 -0.4538061404665817 0.615042066667398 -0.45215310655057755
                    0.6221303946392763 -0.4509607716090181 0.629433060147447 -0.45024083597812686
                    0.636879793620241 -0.45000000000000023 0.6443990980698899 -0.4502407640218737
                    0.6519184025195388 -0.45096062839098244 0.6593651359923328 -0.45215289344942294
                    0.6666678015005035 -0.45380585953341873 0.6737561294723817 -0.4559037269711184
                    0.6805615380334344 -0.4584262960745195 0.6870188207034006 -0.46134926714167207
                    0.6930656861152549 -0.4646444404522729 0.6986436785772808 -0.468280016261793
                    0.7036994054891711 -0.47222119480368047 0.7081840770609893 -0.47642987628495487
                    0.7120544268752448 -0.4808654608840058 0.7152731721679295 -0.48548544874912386
                    0.717809320682543 -0.49024513999629865 0.7196386309511297 -0.4950987347114218
                    0.7207431520132412 -0.4999996329436785 0.7211126042590482 -0.5049005347114219
                    0.7207431520132412 -0.5097541399962988 0.7196386309511297 -0.5145138487491239
                    0.717809320682543 -0.5191338608840059
                    0.7152731721679295</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-no-Storey-Construction-tex-Window_BD.psmdoBp5bySwjmpQTeMD_BP.RwTHVpFyEUcO8zuVwtSe_LR.hSU36yxw5CBRW5wFVjCW</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
        </app:ParameterizedTexture>
      </app:surfaceData>
      <app:surfaceData>
        <app:ParameterizedTexture>
          <app:imageURI>textures/Roofing_Shingles_GAF_Estates.jpg</app:imageURI>
          <app:wrapMode>wrap</app:wrapMode>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_PG.Iu5Q93HicOBRznKlBKqE</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>14.671668539650401 30.716597651817914 15.029578339881674
                    30.438975359730012 15.029578339881676 45.7082016923418 14.671668539650403
                    45.9858239844297 14.671668539650401 30.716597651817914</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_LR.QoAZ8VWB78kYm2QHCFI8</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_PG.2DXeCrnYFTe4NBLbTIGC</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>-8.59246889771538 30.71659765181792 -8.59246889771538
                    30.161353067984578 14.671668539650405 30.161353067984578 14.671668539650405
                    30.71659765181792 -8.59246889771538 30.71659765181792</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_LR.wh2wvw14vCxyRj2iUv7x</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_PG.9FctWwzZPerF6BIy3sqj</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>-8.59246889771539 45.98582398442973 -8.950378697946663
                    45.70820169234183 -8.950378697946661 30.438975359730037 -8.592468897715388
                    30.716597651817942 -8.59246889771539 45.98582398442973</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_LR.Q1wBVMNITizsmPow89Gt</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_PG.oh6S5N4J9aSMQrA5Q4ia</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>14.671668539650407 45.98582398442973 14.671668539650407
                    46.54106856826307 -8.592468897715381 46.54106856826307 -8.592468897715381
                    45.98582398442973 14.671668539650407 45.98582398442973</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_LR.SFEv1iSdjHlJuIbGUoX3</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_PG.HFO41EX8efenwmGi5Eft</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>36.14625694337267 30.438975359730012 36.14625694337267
                    45.70820169234181 12.882119506006884 45.70820169234181 12.882119506006884
                    30.438975359730012 36.14625694337267 30.438975359730012</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_LR.RWrpZWqwlNoeBXW90htk</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_PG.Qaoo4itOZjJIW0peZkt5</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>-8.59246889771538 45.985823984429715 -8.59246889771538
                    30.716597651817917 14.671668539650405 30.716597651817917 14.671668539650405
                    45.985823984429715 -8.59246889771538 45.985823984429715</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_LR.tzqFUfEx4Nk6eMlakzSH</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_PG.1MV05AI6uNdePdx4fxAn</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>22.724639191048468 63.99140850690811 22.724639191048468
                    63.43616392307516 45.988776628397524 63.43616392307516 45.988776628397524
                    63.99140850690811 22.724639191048468 63.99140850690811</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_LR.PjRerCviIUTzOVJxCNyw</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_PG.9bUEvk7j5tVIPNlVW8uJ</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>12.882119506008985 56.35679533589367 12.882119506008985
                    55.80155075206033 22.724639191048354 63.43616392307505 22.724639191048354
                    63.99140850690839 12.882119506008985 56.35679533589367</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_LR.214TSZ9XYDFJXNHLgNHZ</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_PG.aQ3tfZHgKl9ecYAN5Ioo</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>45.98877662839749 79.26063483950891 45.98877662839749
                    79.81587942334185 22.72463919104845 79.81587942334185 22.72463919104845
                    79.26063483950891 45.98877662839749 79.26063483950891</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_LR.3kb3LCU9DvfrQhMIerrl</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_PG.eBexp5vGMTPuTswk1Lqa</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>45.988776628397524 63.99140850690808 46.34668642862854
                    64.26903079899579 46.346686428628544 79.53825713159662 45.988776628397524
                    79.26063483950891 45.988776628397524 63.99140850690808</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_LR.1hufme0bUZmffF5fVafq</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_PG.llAA4hqdggjuq9LXMqqe</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>22.724639191048443 79.8158794233419 45.988776628397495
                    79.8158794233419 45.988776628397495 95.08510575594272 22.724639191048443
                    95.08510575594272 22.724639191048443 79.8158794233419</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_LR.Ov6mkIKl1wlzqUr7dYpr</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
          <app:textureParameterization>
            <app:TextureAssociation>
              <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_PG.V3ha3sDA4z9ACdq9OhrW</app:target>
              <app:textureParameterization>
                <app:TexCoordList>
                  <app:textureCoordinates>45.98877662839752 79.26063483950894 22.724639191048464
                    79.26063483950894 22.724639191048464 63.991408506908115 45.98877662839752
                    63.991408506908115 45.98877662839752 79.26063483950894</app:textureCoordinates>
                  <app:ring>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_LR.G1Is6jtBzZa5hiCOFxqu</app:ring>
                </app:TexCoordList>
              </app:textureParameterization>
            </app:TextureAssociation>
          </app:textureParameterization>
        </app:ParameterizedTexture>
      </app:surfaceData>
      <app:surfaceData>
        <app:X3DMaterial>
          <app:ambientIntensity>0.2</app:ambientIntensity>
          <app:diffuseColor>0.49411764705882355 0.4980392156862745
            0.44313725490196076</app:diffuseColor>
          <app:emissiveColor>0.0 0.0 0.0</app:emissiveColor>
          <app:specularColor>1.0 1.0 1.0</app:specularColor>
          <app:shininess>0.2</app:shininess>
          <app:transparency>0.0</app:transparency>
          <app:isSmooth>false</app:isSmooth>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_PG.xJxsIZemRugiHB0gL5h6</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_PG.QOcD5lDTtfLZxmwl1Zwu</app:target>
        </app:X3DMaterial>
      </app:surfaceData>
      <app:surfaceData>
        <app:X3DMaterial>
          <app:ambientIntensity>0.2</app:ambientIntensity>
          <app:diffuseColor>0.8117647058823529 0.8117647058823529
            0.8117647058823529</app:diffuseColor>
          <app:emissiveColor>0.0 0.0 0.0</app:emissiveColor>
          <app:specularColor>1.0 1.0 1.0</app:specularColor>
          <app:shininess>0.2</app:shininess>
          <app:transparency>0.0</app:transparency>
          <app:isSmooth>false</app:isSmooth>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.NuNgbvh89KUaU7XcKYUI</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.SkQ1rqOSiiV6z6rQY7GU</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.7lmPQ81QGPKvuCTrEOSx</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.Kwmv6nB3tfpmhbXAL7nY</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.IcNXv53aAiAf2cDQC2Ew</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.MVOQRduYfbqKfESybtGu</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.PIfvzvWWSzYur9lPkacC</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.FqtCUBIfZ5bxz3316yiW</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.NpYKpOGWkPe9lowTp47V</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.lfroSmlAjpjCdP0N6iKD</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.lSWao7HQmKNrbs6PnU2K</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.Va6PI4eI8VJzLeR5y7tC</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.EXAhFSCfswxY804ozzBf</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.D5CMrrjCZQy3x6jkPXKE</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.cms7HTJt4aS9N3WWAlmD</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.2xepsHwio6EWFmZNT1Jx</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.DBX6vx2V6CrFOGig4PUo</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.sOAjMic9c7isncdb0L83</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.98yMmpoQXs5BB8nXxfG9</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.UESzjRItWh3clkyc6Hgz</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.yoLDnur9D7wsl8xB8Gj0</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.3MFcfHVPs9BGmyzDAVgg</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.GN8DA1oDOnCUrimftzTj</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.Y7BpEs72xSPbGra4QPxW</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.4gTm9Bn7UbEWgQC8bSjy</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.b3mjhZdQleXFPUFsFOtI</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.hw3f6eDbUYzCmHsHFes4</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.LyKVhIOZtjzTySwNZTdg</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.0wA1hgHax9ZFpRFs70nr</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.ZZnKeSo7EXJSy2gZCycZ</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.Kqka9dTOu58LJgLRf6oy</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.iCnyy2BdLJAogLSs2i51</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.1jD7aTdoiCN3mQEEU42p</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.MX4Zm8jk3QUlybqISaBT</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.5x2UcEXiuHs9EvbsMsVN</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.TEySNz7HuCioG969UenF</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.YG5U5xi5KTUBxmf1iulN</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.bFZVcr6XLcXsJJwtRSSA</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.u1Xnrdz79ayx2kQ1pkpt</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.nBlDAapwzX2tqPLlwVbM</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.mxHNopzAdsGpwWldh3jf</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.MXGACnPExMsY4UiCGrB8</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.UJWd7iJ2rz9gw0Qaciao</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.aqE6OEqSUsgw6xdVacvi</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.85JPhnkJXV9VCUEij5l1</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.MnianrJYS1uOj6nfGUh2</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.8Psj4NMvO34m3cvY6kHy</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.p9iCOl21RCJtgwdDHv3H</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.kQNdgKDffLSyMXVlMMNK</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.UcVah209j0Ktz9lwhFgf</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.0sFhg9grcQeaAez3S1Fd</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.TlgO9waAmYuRJoSvYD6C</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.1EZrBaUWdkbKInql9bZ3</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.1yUVEQ1OnJ45W9MwUdiz</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.0Vbkm1FF5ocf5wsl8ROm</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.Pc79XMOMb9epJn2eIztW</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.aSsju6BwCWKIfjvQ6NOr</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.X1v589eDY3eWLIZGaV2f</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.9Pf9ymItQA6c2I2WvtV5</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.yuP7cbU7A3IxfCFGy97D</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.BpdaCGTkNdGGdyOQrqkl</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.99Q5UITX3dQ5iiv8R5vZ</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.OaIh1pItuIcY4oibiKgA</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.otkas6NaobDYfzhMCJfV</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.UVrxYZII6B07b0qMLJrH</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.UEsVvjvM5Jz8PYGCu8fy</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.6lihCSiX29syQkjRSItD</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.XVjic4mVD39DMieFeozC</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.cK7Qrhr6BbYvY2KiqAmX</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.7XVKzDCkWgUbYmcAVZsw</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.VEmwUZIgRr4PmgJQYTCE</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.32oKLqzJJuhPro9wzPxQ</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.WwoHLUHpTnrRGiXsBBpl</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.Br2AkE40jBPaztO4NK5c</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.Q3VRDplBcf5Sn8A7gJSe</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.JTtUUOecuPI2zWmffEdW</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.cmJhj4LtBVXujMI6c4fP</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.tEmaCEhbmqm9yc3olLdv</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.CSQGsLiLq3TR3QFz0zNh</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.7uCK71niQJNpSk6q6bQo</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.Yxco1ZKuRESx19QSj0Ec</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.6Wz85yeHKNQzPzl71hi2</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.XXDJ0dn3Utm5YQE82uIp</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.KEw8qErkzHoHmAdfFVNZ</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.yVYH5rtHSoKQiGJOg7g4</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.XzSoGRhq9BNX6v1nTE2B</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.4vBTyMX4CrNwX8AP8FXO</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.DMQvRTwMHeBvJNxvpNYk</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.WQbQrFJ08GbR9rDwF9Tj</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.NX0Kd1iQoq0sf5YQ5FCb</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.J9Fp8cQZDHeibcKpYA6M</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.3ydcErzYTjbEfxDkhJhh</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.b0ytGkB5KLl3yiTDwNQ5</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.WJEfneenBWpaTrlEBT3T</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.nExgADm8B1h386ydIETU</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.3gfu9ZHLlmAI5f2PGNzl</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.EtTRgHKjral4sltWvrnn</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.oRHkWlGVSz67ZJEylnUJ</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.GOKaBV66BjDiQcEmftsA</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.F3YqqiO6CHw36e7hFQ3Q</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.lojs9PFJ38v0Ac2FlayC</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.hOsB4PbVnX0n6AJWJP4T</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.JHj2MHKpOhSxeyqTZAXz</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.N9W5smybE3KLTUYlVY3J</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.gO0UK2sWLNbx8VWU2orT</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.vt8nuJSwRSBSaS4WynMx</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.npdFCZK2weUEYSC1WxOs</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.ikJAa67vOHW4LNHsJiZP</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.0hbjpY12KJgwMDw4gXXf</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.ZM7uRaMR6epZv4nbEoKc</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.xCH1FMvSuWoKTD8Jgc6a</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.ygnnB5QxYl2s6xA1JZfV</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.KF35NJJqUDA8D49R0CNi</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.Q7nGcN8I200dKCydPhPU</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.q52JInCbEMGS9IlmcvAE</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.UGeS0MvCsvAQApaMN7Cz</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.oPZesjL2cR2Ep4JgWH4q</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.ExfgmrmOYW8V4p5KKYuq</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.d7SHai1vlIzwTYXRwrRO</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.2QP3AcH9syeNWcs2ycek</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.BpYJrR0aijAoaupYr1t0</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.QUdrRF2GFKFWxCqaL03v</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.CFmcf6rQMPyaT8Bd1NNx</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.P42tyRKb1TZPnnNyIPQZ</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.o5DM4dQHJi8AxeXJrjWd</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.zTR9KD9pVT0SAHLpJ0ms</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.U1Zj8M2rxDi24SDg5w8T</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.rR9jsnKpjJdrkuWAtWdg</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_PG.jNQboPa0u7w243GPebem</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_PG.EirHVMjm9hy5SkvMdLy0</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_PG.CfVzf3WfhmyHf8PYo4JS</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_PG.XnYHk4ccnzcYlu8QmWho</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_PG.7BAluzsqrefXamIThALm</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_PG.DAmp37PMEKiVkGsL0ms6</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_PG.l6nc2LexYlHeDl7BXm0N</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_PG.HaQve8yxYRhl4EcMD55u</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_PG.o2m6wWfVQq6z9PpRino3</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_PG.QZv6P5CusqLtsdu3RFf7</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.xsKWsYE4QDecGyP5gnoP</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.GJKHOoZjPUWGT7WmvtYo</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.eFksVmNchId214tQlSQ4</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.OyfNYZGU0Gq9iRGhIeLN</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.nLQJjcyjN5v5GPOwLZHS</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.5oRrsKRU1HWXsxniKHPy</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.S5hjnW5f4RTmUNXhajTm</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.RYEQV8PDhrzLe6rGYu69</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.lNi8zFN1xc8zlTLCnXxb</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.9UZiJ4W3dVSChw9hSdhI</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.lCzFtw4hrU6T6gNkGeXK</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.LrzH813FWTwg49px8uZK</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.t337iQ17r02Tkh9o5jox</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.FqSnOIQmCNlbZ7EUG65P</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.woAg1vYaxJBPjUVLvNgX</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.1roawYgfujIWUmybzfVY</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.Is27JY3f1wMLCC07MrYf</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.5WOOxXlwkr29D71364vr</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.OBOqtpWkIsKpPIak3kWU</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.j4nXWbRdJB3vEOwx0rb0</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.xqz6S2wvc1WmnmF8TJPV</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.FrtFDmApoIOOFmWSng1T</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.HTlUzjLhhEZgA8EoxURH</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.pLCFknO9ipWFZVuh4g5s</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.EbR3oSx11uVKRsPhfVAo</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.iieDp8XsFrxDprm3YXrR</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.B8X0nUEaCjW4AyFUTI5l</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.lS5KrYBAMAxoJhQZLwsV</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.bWEg6PPxX2ioVJjzutXB</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.zPD9dJQk2mKPhEohoKNR</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.8GylgWKHjJ32mhqIG7sk</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.GYwo7PvXwezoJ7EnHSC3</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.bMdGYSY2nhP2zKk0GaMI</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.z1BouNhDpqt7L44vUdZI</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.xuLKaAj8WJRwemujOLQo</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.LFkbrK5JaXzL33DWpyvf</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.nK1Ziur1nFzkCdjmPmni</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.DNn1h6v9Eg3PCHvGir2c</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.iuCZmNsxIJM4yoH8zwrQ</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.rYBdvGRTXg4SuxsTcK4Q</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.g1zW7JMWvhdyvZTGNB8I</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.plNZqyrCrOmEMZSzqebB</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.kHRICSOXPh0HYikbTRRW</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.6JXZtlF2HvZilOcWLC7B</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.A7PkEeDFsbc7cc1pnzoM</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.Dh2B2Il3hOpzZ0R3yXK3</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.XWtd5xDtGAvldhO4b7iV</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.fsA97wwpxRVOh3jgQzoN</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.tJAWU8AaLYc7PT4Fe4w2</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.02adiHKX2M8am0Lw5NDY</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.80RtE0PFNi0PWWsAdD2o</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.BdxHs3b7FRTb9olheU7H</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.9znC8SMkIVXi49sgyYNm</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.t8ER9tftSyYShIvXE4UO</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.GV0TEeZyYTZ63PQyf0LB</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.lovYLrc4E8dazm8XnJ6Q</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.LZifWJX7l9715oerySwI</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.kFBez9OCnicNk4csTN7C</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.sngyi2DzU5ABBIN1JSow</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.ePeBedPTY8R8RxNnsIgo</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.BuHftk0uQsq3XvG1gxJS</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.D3JjIdZ8CZ5VWArZ2VNC</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.09fGcZ1dtDvtggyFYYMK</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.Q4igxW57I1jbX6eRUrzl</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.qEQYqSSVQ6ih7BTkSHVt</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.5GkJ2pZ35cyTlAN4N4J7</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.BDLFVNTn1QrAVlxoF9GR</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.gYjDP0kyy9JJjqh3RzWB</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.b1F3OTLWJuHSP14HsOEr</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.d7wGMMPC069n5yP6QmxC</app:target>
        </app:X3DMaterial>
      </app:surfaceData>
      <app:surfaceData>
        <app:X3DMaterial>
          <app:isFront>false</app:isFront>
          <app:ambientIntensity>0.2</app:ambientIntensity>
          <app:diffuseColor>0.49411764705882355 0.4980392156862745
            0.44313725490196076</app:diffuseColor>
          <app:emissiveColor>0.0 0.0 0.0</app:emissiveColor>
          <app:specularColor>1.0 1.0 1.0</app:specularColor>
          <app:shininess>0.2</app:shininess>
          <app:transparency>0.0</app:transparency>
          <app:isSmooth>false</app:isSmooth>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_PG.xJxsIZemRugiHB0gL5h6</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_PG.QOcD5lDTtfLZxmwl1Zwu</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_PG.e9AMeV0pEURTngbpCIid</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_PG.hNmG4YmoXQMBm8b42JJ4</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_PG.vgpO7agF1kI7rJRF6jCg</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.Um20q9TChr2VYbrcN9zj_PG.MgxBTndXeCqtGtBjgXrT</app:target>
        </app:X3DMaterial>
      </app:surfaceData>
      <app:surfaceData>
        <app:X3DMaterial>
          <app:isFront>false</app:isFront>
          <app:ambientIntensity>0.2</app:ambientIntensity>
          <app:diffuseColor>0.8117647058823529 0.8117647058823529
            0.8117647058823529</app:diffuseColor>
          <app:emissiveColor>0.0 0.0 0.0</app:emissiveColor>
          <app:specularColor>1.0 1.0 1.0</app:specularColor>
          <app:shininess>0.2</app:shininess>
          <app:transparency>0.0</app:transparency>
          <app:isSmooth>false</app:isSmooth>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.NuNgbvh89KUaU7XcKYUI</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.SkQ1rqOSiiV6z6rQY7GU</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.7lmPQ81QGPKvuCTrEOSx</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.Kwmv6nB3tfpmhbXAL7nY</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.IcNXv53aAiAf2cDQC2Ew</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.GhhgkoiACRoutZj6gPJD</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.MVOQRduYfbqKfESybtGu</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.PIfvzvWWSzYur9lPkacC</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.FqtCUBIfZ5bxz3316yiW</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.NpYKpOGWkPe9lowTp47V</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.lfroSmlAjpjCdP0N6iKD</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.lSWao7HQmKNrbs6PnU2K</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.Va6PI4eI8VJzLeR5y7tC</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.EXAhFSCfswxY804ozzBf</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.D5CMrrjCZQy3x6jkPXKE</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.cms7HTJt4aS9N3WWAlmD</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.2xepsHwio6EWFmZNT1Jx</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.SJPk8PlD4ohhHNDBxNmY_PG.DBX6vx2V6CrFOGig4PUo</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.sOAjMic9c7isncdb0L83</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.98yMmpoQXs5BB8nXxfG9</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.UESzjRItWh3clkyc6Hgz</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.yoLDnur9D7wsl8xB8Gj0</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.3MFcfHVPs9BGmyzDAVgg</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.vPkHyW4ZqK4NBbln6BPU</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.oGvYxDaN7tEMUBruq989</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.aaC58mJm7tRYJrf71O1t</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.A5iro2UuhcRvA0U5UnAX</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.1p4KTXynAoyl6e166LeS</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.GN8DA1oDOnCUrimftzTj</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.KcjNlHb2379iNGJW8tBO</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.wTrfNM4Oxh3XEeBTCyf9</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.uQkogrP58iI8nzgckJU8_PG.Y7BpEs72xSPbGra4QPxW</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.4gTm9Bn7UbEWgQC8bSjy</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.b3mjhZdQleXFPUFsFOtI</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.hw3f6eDbUYzCmHsHFes4</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.LyKVhIOZtjzTySwNZTdg</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.0wA1hgHax9ZFpRFs70nr</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.Ak1NLFqBgU5p93bMXwFH</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.ZZnKeSo7EXJSy2gZCycZ</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.Kqka9dTOu58LJgLRf6oy</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.iCnyy2BdLJAogLSs2i51</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.1jD7aTdoiCN3mQEEU42p</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.MX4Zm8jk3QUlybqISaBT</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.5x2UcEXiuHs9EvbsMsVN</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.TEySNz7HuCioG969UenF</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.YG5U5xi5KTUBxmf1iulN</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.bFZVcr6XLcXsJJwtRSSA</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.u1Xnrdz79ayx2kQ1pkpt</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.nBlDAapwzX2tqPLlwVbM</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.bgLnENgBqpdd0kYq3k5B_PG.mxHNopzAdsGpwWldh3jf</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.MXGACnPExMsY4UiCGrB8</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.UJWd7iJ2rz9gw0Qaciao</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.aqE6OEqSUsgw6xdVacvi</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.85JPhnkJXV9VCUEij5l1</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.MnianrJYS1uOj6nfGUh2</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.pT57K3pbUX6MaTHCDERp</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.8Psj4NMvO34m3cvY6kHy</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.p9iCOl21RCJtgwdDHv3H</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.kQNdgKDffLSyMXVlMMNK</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.UcVah209j0Ktz9lwhFgf</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.0sFhg9grcQeaAez3S1Fd</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.TlgO9waAmYuRJoSvYD6C</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.1EZrBaUWdkbKInql9bZ3</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.1yUVEQ1OnJ45W9MwUdiz</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.0Vbkm1FF5ocf5wsl8ROm</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.Pc79XMOMb9epJn2eIztW</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.aSsju6BwCWKIfjvQ6NOr</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.GLZsSarMcKYWLuH3T7Br_PG.X1v589eDY3eWLIZGaV2f</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.9Pf9ymItQA6c2I2WvtV5</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.yuP7cbU7A3IxfCFGy97D</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.BpdaCGTkNdGGdyOQrqkl</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.99Q5UITX3dQ5iiv8R5vZ</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.OaIh1pItuIcY4oibiKgA</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.otkas6NaobDYfzhMCJfV</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.gEUqSoYeOFLY26aPvwVa</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.UVrxYZII6B07b0qMLJrH</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.UEsVvjvM5Jz8PYGCu8fy</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.6lihCSiX29syQkjRSItD</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.XVjic4mVD39DMieFeozC</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.cK7Qrhr6BbYvY2KiqAmX</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.7XVKzDCkWgUbYmcAVZsw</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.VEmwUZIgRr4PmgJQYTCE</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.32oKLqzJJuhPro9wzPxQ</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.WwoHLUHpTnrRGiXsBBpl</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.Br2AkE40jBPaztO4NK5c</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.Q3VRDplBcf5Sn8A7gJSe</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.JTtUUOecuPI2zWmffEdW</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.cmJhj4LtBVXujMI6c4fP</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.tEmaCEhbmqm9yc3olLdv</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.CSQGsLiLq3TR3QFz0zNh</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.7uCK71niQJNpSk6q6bQo</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.Yxco1ZKuRESx19QSj0Ec</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.6Wz85yeHKNQzPzl71hi2</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.XXDJ0dn3Utm5YQE82uIp</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.KEw8qErkzHoHmAdfFVNZ</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.yVYH5rtHSoKQiGJOg7g4</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.XzSoGRhq9BNX6v1nTE2B</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.4vBTyMX4CrNwX8AP8FXO</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.DMQvRTwMHeBvJNxvpNYk</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.WQbQrFJ08GbR9rDwF9Tj</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.NX0Kd1iQoq0sf5YQ5FCb</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.J9Fp8cQZDHeibcKpYA6M</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.3ydcErzYTjbEfxDkhJhh</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.b0ytGkB5KLl3yiTDwNQ5</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.WJEfneenBWpaTrlEBT3T</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.nExgADm8B1h386ydIETU</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.3gfu9ZHLlmAI5f2PGNzl</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.EtTRgHKjral4sltWvrnn</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.oRHkWlGVSz67ZJEylnUJ</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.GOKaBV66BjDiQcEmftsA</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.F3YqqiO6CHw36e7hFQ3Q</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.lojs9PFJ38v0Ac2FlayC</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.hOsB4PbVnX0n6AJWJP4T</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.JHj2MHKpOhSxeyqTZAXz</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.N9W5smybE3KLTUYlVY3J</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.gO0UK2sWLNbx8VWU2orT</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.vt8nuJSwRSBSaS4WynMx</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.npdFCZK2weUEYSC1WxOs</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.ikJAa67vOHW4LNHsJiZP</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.0hbjpY12KJgwMDw4gXXf</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.ZM7uRaMR6epZv4nbEoKc</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.xCH1FMvSuWoKTD8Jgc6a</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.ygnnB5QxYl2s6xA1JZfV</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.KF35NJJqUDA8D49R0CNi</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.Q7nGcN8I200dKCydPhPU</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.q52JInCbEMGS9IlmcvAE</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.UGeS0MvCsvAQApaMN7Cz</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.oPZesjL2cR2Ep4JgWH4q</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.ExfgmrmOYW8V4p5KKYuq</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.d7SHai1vlIzwTYXRwrRO</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.2QP3AcH9syeNWcs2ycek</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.BpYJrR0aijAoaupYr1t0</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.QUdrRF2GFKFWxCqaL03v</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.CFmcf6rQMPyaT8Bd1NNx</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.P42tyRKb1TZPnnNyIPQZ</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.o5DM4dQHJi8AxeXJrjWd</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.zTR9KD9pVT0SAHLpJ0ms</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.U1Zj8M2rxDi24SDg5w8T</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.p5veIaWHYI0ERF6P79Qh_PG.rR9jsnKpjJdrkuWAtWdg</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_PG.jNQboPa0u7w243GPebem</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_PG.EirHVMjm9hy5SkvMdLy0</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_PG.CfVzf3WfhmyHf8PYo4JS</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_PG.XnYHk4ccnzcYlu8QmWho</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_PG.7BAluzsqrefXamIThALm</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.FqDUwbEoWeqSVnBzuFGf_PG.6s7V4a1OB8u1aTStTcbJ</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_PG.DAmp37PMEKiVkGsL0ms6</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_PG.l6nc2LexYlHeDl7BXm0N</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_PG.HaQve8yxYRhl4EcMD55u</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_PG.o2m6wWfVQq6z9PpRino3</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_PG.QZv6P5CusqLtsdu3RFf7</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.vpU9KsYEd1yCdBhkTvW9_PG.2dKXmAy0meKvCww51jj9</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.xsKWsYE4QDecGyP5gnoP</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.GJKHOoZjPUWGT7WmvtYo</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.eFksVmNchId214tQlSQ4</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.OyfNYZGU0Gq9iRGhIeLN</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.nLQJjcyjN5v5GPOwLZHS</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.5oRrsKRU1HWXsxniKHPy</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.wWxjhW73retZkAs8CSXd</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.S5hjnW5f4RTmUNXhajTm</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.RYEQV8PDhrzLe6rGYu69</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.lNi8zFN1xc8zlTLCnXxb</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.9UZiJ4W3dVSChw9hSdhI</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.lCzFtw4hrU6T6gNkGeXK</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.LrzH813FWTwg49px8uZK</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.t337iQ17r02Tkh9o5jox</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.FqSnOIQmCNlbZ7EUG65P</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.woAg1vYaxJBPjUVLvNgX</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.1roawYgfujIWUmybzfVY</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.Is27JY3f1wMLCC07MrYf</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.5WOOxXlwkr29D71364vr</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.OBOqtpWkIsKpPIak3kWU</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.j4nXWbRdJB3vEOwx0rb0</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.xqz6S2wvc1WmnmF8TJPV</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.FrtFDmApoIOOFmWSng1T</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.HTlUzjLhhEZgA8EoxURH</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.pLCFknO9ipWFZVuh4g5s</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.EbR3oSx11uVKRsPhfVAo</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.iieDp8XsFrxDprm3YXrR</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.B8X0nUEaCjW4AyFUTI5l</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.lS5KrYBAMAxoJhQZLwsV</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.bWEg6PPxX2ioVJjzutXB</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.zPD9dJQk2mKPhEohoKNR</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.8GylgWKHjJ32mhqIG7sk</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.GYwo7PvXwezoJ7EnHSC3</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.bMdGYSY2nhP2zKk0GaMI</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.z1BouNhDpqt7L44vUdZI</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.xuLKaAj8WJRwemujOLQo</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.LFkbrK5JaXzL33DWpyvf</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.nK1Ziur1nFzkCdjmPmni</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.DNn1h6v9Eg3PCHvGir2c</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.iuCZmNsxIJM4yoH8zwrQ</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.rYBdvGRTXg4SuxsTcK4Q</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.g1zW7JMWvhdyvZTGNB8I</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.plNZqyrCrOmEMZSzqebB</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.kHRICSOXPh0HYikbTRRW</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.6JXZtlF2HvZilOcWLC7B</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.A7PkEeDFsbc7cc1pnzoM</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.Dh2B2Il3hOpzZ0R3yXK3</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.XWtd5xDtGAvldhO4b7iV</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.fsA97wwpxRVOh3jgQzoN</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.tJAWU8AaLYc7PT4Fe4w2</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.02adiHKX2M8am0Lw5NDY</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.80RtE0PFNi0PWWsAdD2o</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.BdxHs3b7FRTb9olheU7H</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.9znC8SMkIVXi49sgyYNm</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.t8ER9tftSyYShIvXE4UO</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.GV0TEeZyYTZ63PQyf0LB</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.lovYLrc4E8dazm8XnJ6Q</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.LZifWJX7l9715oerySwI</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.kFBez9OCnicNk4csTN7C</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.sngyi2DzU5ABBIN1JSow</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.ePeBedPTY8R8RxNnsIgo</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.BuHftk0uQsq3XvG1gxJS</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.D3JjIdZ8CZ5VWArZ2VNC</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.09fGcZ1dtDvtggyFYYMK</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.Q4igxW57I1jbX6eRUrzl</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.qEQYqSSVQ6ih7BTkSHVt</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.5GkJ2pZ35cyTlAN4N4J7</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.BDLFVNTn1QrAVlxoF9GR</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.gYjDP0kyy9JJjqh3RzWB</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.b1F3OTLWJuHSP14HsOEr</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.mXNKW1u7H3aIheseoeR9_PG.d7wGMMPC069n5yP6QmxC</app:target>
        </app:X3DMaterial>
      </app:surfaceData>
      <app:surfaceData>
        <app:X3DMaterial>
          <app:isFront>false</app:isFront>
          <app:ambientIntensity>0.2</app:ambientIntensity>
          <app:diffuseColor>0.7450980392156863 0.33725490196078434
            0.09411764705882353</app:diffuseColor>
          <app:emissiveColor>0.0 0.0 0.0</app:emissiveColor>
          <app:specularColor>1.0 1.0 1.0</app:specularColor>
          <app:shininess>0.2</app:shininess>
          <app:transparency>0.0</app:transparency>
          <app:isSmooth>false</app:isSmooth>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_PG.Iu5Q93HicOBRznKlBKqE</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_PG.2DXeCrnYFTe4NBLbTIGC</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_PG.9FctWwzZPerF6BIy3sqj</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_PG.oh6S5N4J9aSMQrA5Q4ia</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_PG.HFO41EX8efenwmGi5Eft</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.jljibiSayVm3Kqm8moFr_PG.Qaoo4itOZjJIW0peZkt5</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_PG.1MV05AI6uNdePdx4fxAn</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_PG.9bUEvk7j5tVIPNlVW8uJ</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_PG.aQ3tfZHgKl9ecYAN5Ioo</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_PG.eBexp5vGMTPuTswk1Lqa</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_PG.llAA4hqdggjuq9LXMqqe</app:target>
          <app:target>#_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz_BP.hA4lmON8U7EsPT2SaIOi_PG.V3ha3sDA4z9ACdq9OhrW</app:target>
        </app:X3DMaterial>
      </app:surfaceData>
    </app:Appearance>
  </core:appearanceMember>
  <core:appearanceMember>
    <app:Appearance gml:id="ID_ef2cc176-b404-3b57-8cd7-0ac1d8f81af8">
      <app:surfaceData>
        <app:X3DMaterial>
          <app:ambientIntensity>0.2</app:ambientIntensity>
          <app:diffuseColor>0.49411764705882355 0.4980392156862745
            0.44313725490196076</app:diffuseColor>
          <app:emissiveColor>0.0 0.0 0.0</app:emissiveColor>
          <app:specularColor>1.0 1.0 1.0</app:specularColor>
          <app:shininess>0.2</app:shininess>
          <app:transparency>0.0</app:transparency>
          <app:isSmooth>false</app:isSmooth>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.Bd2v6nBBghEwrOLuMRpO_PG.Au8s79L1OzNGg3DYcb1i</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.Bd2v6nBBghEwrOLuMRpO_PG.tkFsuKNUmgfely84Z0id</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.Bd2v6nBBghEwrOLuMRpO_PG.1oIln8w50rEyFGmWQGda</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.Bd2v6nBBghEwrOLuMRpO_PG.lkEXqAsPGgzYYpSISIuY</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.Bd2v6nBBghEwrOLuMRpO_PG.di297lmDY2x3chLBO7lY</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.Bd2v6nBBghEwrOLuMRpO_PG.vEPjFMb5Bfk4n6lFDwdY</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.Bd2v6nBBghEwrOLuMRpO_PG.vYKxuio9jeY5YBX5FuoX</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.Bd2v6nBBghEwrOLuMRpO_PG.QZc36E47EpExUHOOe3Pp</app:target>
        </app:X3DMaterial>
      </app:surfaceData>
      <app:surfaceData>
        <app:X3DMaterial>
          <app:ambientIntensity>0.2</app:ambientIntensity>
          <app:diffuseColor>0.8117647058823529 0.8117647058823529
            0.8117647058823529</app:diffuseColor>
          <app:emissiveColor>0.0 0.0 0.0</app:emissiveColor>
          <app:specularColor>1.0 1.0 1.0</app:specularColor>
          <app:shininess>0.2</app:shininess>
          <app:transparency>0.0</app:transparency>
          <app:isSmooth>false</app:isSmooth>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.qRkdlaRa8N0CQtbdEIFv_PG.d8kVAyrlEU9CrfA8A2gW</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.qRkdlaRa8N0CQtbdEIFv_PG.uJsLK8i5SurJiExGFyi3</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.qRkdlaRa8N0CQtbdEIFv_PG.FCQY9L7oBdnfiY6rV26u</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.qRkdlaRa8N0CQtbdEIFv_PG.6kA59FxHoahxQqrUEIte</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.qRkdlaRa8N0CQtbdEIFv_PG.XnNFobF5UIP6j0uH8aj5</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.qRkdlaRa8N0CQtbdEIFv_PG.dy7w8BKNhuDhLWCtEvMD</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.tevoh8uvM5ObHej38qSR</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.ivw57JFf2lTDeLw4Ibtn</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.PEFnRCNDFqbEaU7t0w7Z</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.4Kz1yToBEi5liZmlaZh5</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.Dsw1ReWByNvMnfqrQVa4</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.EDfoUPuFxA56P18CIw6h</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.gHBb4dieFnO2YLCkbCXW</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.C4amUICXdGbBS8306cSz</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.8VNFSjoGbq08vqjB0gG4</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.TyPnnB5IO8HVuhbnoC9q</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.0vivLw0vUbUszB4tBrKk</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.AoqmwbSIvGPHY36XjJzi</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.2kp4YIe3H41GTYqmqzeF</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.JsXaletve9OxXGrBcXNd_PG.9A5t86IpOPzmFEZBLaJz</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.R1DJ5JpOrRkQXkwPmUBa_PG.hxsvwtyAn5axgrUjw5WN</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.R1DJ5JpOrRkQXkwPmUBa_PG.oTZeCOYgqyCjdwhXqlqP</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.R1DJ5JpOrRkQXkwPmUBa_PG.5EpvkqWfeZT294U7KZaX</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.R1DJ5JpOrRkQXkwPmUBa_PG.NJZouCBgRo0ocAOH7S2B</app:target>
          <app:target>#UUID_8914e1c3-ea3a-4d49-9a04-14c6d3ef6ea3</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.R1DJ5JpOrRkQXkwPmUBa_PG.fEegQAGXMwPfM29hj4Jp</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.DQjKZ7HGEqZ7Z3ubUp0N_PG.35Ew3lUPb7MKZrZjk1lq</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.DQjKZ7HGEqZ7Z3ubUp0N_PG.RhAkTStqrkUoYKWMY5ay</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.DQjKZ7HGEqZ7Z3ubUp0N_PG.W7a53czBjI5fGEOkxRhm</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.DQjKZ7HGEqZ7Z3ubUp0N_PG.aGfkflazY9Z022vmKreZ</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.DQjKZ7HGEqZ7Z3ubUp0N_PG.3t0rTpC2wit2gUeLZ3ua</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.DQjKZ7HGEqZ7Z3ubUp0N_PG.XCqVAzhRwVkldJT6lLSP</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.7B9cENkB33kDDJ3LwzGe</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.ge6tBACJRyFV56CWHEzA</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.7aGP838SmLScKDpjVjvk</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.5yZhBXvPX1yQmmawrZir</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.nrQ6ruhxHc4uf9SPzen7</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.8cTY19D4y3xawTYYl4av</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.x1aYJYAwBW3WPvfk1tHY</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.1CGknnSuXNhCilZOKJ4t</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.KLuDhHDCBMAxDavA6wtK</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.UPinHSpfpkrmWhCnV5W0_PG.cAXauiJAb8w8JmB8JScQ</app:target>
        </app:X3DMaterial>
      </app:surfaceData>
      <app:surfaceData>
        <app:X3DMaterial>
          <app:ambientIntensity>0.2</app:ambientIntensity>
          <app:diffuseColor>0.5764705882352941 0.45098039215686275
            0.27058823529411763</app:diffuseColor>
          <app:emissiveColor>0.0 0.0 0.0</app:emissiveColor>
          <app:specularColor>1.0 1.0 1.0</app:specularColor>
          <app:shininess>0.2</app:shininess>
          <app:transparency>0.0</app:transparency>
          <app:isSmooth>false</app:isSmooth>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.DoaCjMeE7wRjFY1VZlF3</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.wLHm56rDZnjOqHhmES66</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.DpINacYwpfduPx1yRDjS</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.HBYn9IMWyNmmyGkNStCs</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.z7d6kVNAoAERqCrq30mr</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.5yqkqjxgualuoLP6R7gV</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.i8qamHuiV0I33clMretC</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.aVWByvyZ5GXpT3p1Yb1n</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.6Ph2Vopb23et08Y9OPKl</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.Jp6ofnf9ghbPSHxgQQGD</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.RkJIvpcVwBNQf4noeoay</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.T4fe9wRepB0JAE4Jgyk9</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.S4cjevrMiB08tLVcvpbt_PG.qigoD3DkmcLetNdTV1jc</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.S4cjevrMiB08tLVcvpbt_PG.JjGGVrHaxzjahKoY3UTU</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.S4cjevrMiB08tLVcvpbt_PG.xjYYVWMc8hpf5UDFA7nQ</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.S4cjevrMiB08tLVcvpbt_PG.miOcSXhUmXAyQxbRzaRq</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.S4cjevrMiB08tLVcvpbt_PG.yUAhidnLEVKcjQv9a3K1</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.S4cjevrMiB08tLVcvpbt_PG.CKT9RydeebnO38lN8YxL</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.ndMdKaHqHsTNYxoA22I4_PG.Xa9GyqpsPzN24MDzHbTn</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.ndMdKaHqHsTNYxoA22I4_PG.X6blngoQWbijGXoskrmf</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.ndMdKaHqHsTNYxoA22I4_PG.vl76leAIUtpKkt3zW0hT</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.ndMdKaHqHsTNYxoA22I4_PG.m5aniKKE8QA4x8MKMX7L</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.ndMdKaHqHsTNYxoA22I4_PG.NIZLSIFLwMD5JtEalVWd</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.ndMdKaHqHsTNYxoA22I4_PG.0k5Xo1Cshx34V88a6RTR</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.ZVLOAloklMK3sl7leFKU_PG.Vf8fOK0ooOc2ASNntwTz</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.ZVLOAloklMK3sl7leFKU_PG.Iz4ZBl4yTYEAiKyuQuGk</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.ZVLOAloklMK3sl7leFKU_PG.sHiD8NjLLWIvEideopmW</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.ZVLOAloklMK3sl7leFKU_PG.pN7xEGh1tE2QFhsB5NJ3</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.ZVLOAloklMK3sl7leFKU_PG.xBPEJonLeNMyONoDn60v</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.ZVLOAloklMK3sl7leFKU_PG.pthjYxD2taiINiLHE22G</app:target>
        </app:X3DMaterial>
      </app:surfaceData>
      <app:surfaceData>
        <app:X3DMaterial>
          <app:isFront>false</app:isFront>
          <app:ambientIntensity>0.2</app:ambientIntensity>
          <app:diffuseColor>0.5764705882352941 0.45098039215686275
            0.27058823529411763</app:diffuseColor>
          <app:emissiveColor>0.0 0.0 0.0</app:emissiveColor>
          <app:specularColor>1.0 1.0 1.0</app:specularColor>
          <app:shininess>0.2</app:shininess>
          <app:transparency>0.0</app:transparency>
          <app:isSmooth>false</app:isSmooth>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.DoaCjMeE7wRjFY1VZlF3</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.wLHm56rDZnjOqHhmES66</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.DpINacYwpfduPx1yRDjS</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.HBYn9IMWyNmmyGkNStCs</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.z7d6kVNAoAERqCrq30mr</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.5yqkqjxgualuoLP6R7gV</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.i8qamHuiV0I33clMretC</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.aVWByvyZ5GXpT3p1Yb1n</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.6Ph2Vopb23et08Y9OPKl</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.Jp6ofnf9ghbPSHxgQQGD</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.RkJIvpcVwBNQf4noeoay</app:target>
          <app:target>#_Construstruction-Inner-Walls-Openings_BD.5DRLcV6kCJfkmzW0XwK5_PG.T4fe9wRepB0JAE4Jgyk9</app:target>
        </app:X3DMaterial>
      </app:surfaceData>
    </app:Appearance>
  </core:appearanceMember>
</core:CityModel>
