<?xml version="1.0" encoding="utf-8"?>
<!-- Exported with 3DIS GmbH (https://www.3dis.de) CityEditor 2.26.2.0 -->
<!-- Date: 2023-02-24 17:04:49 +0100 ModelName: -->
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
        <bldg:Building gml:id="_FZK-Haus-Storey-Construction_BD.DX9Xm6VLbbyLGAxG2v86">
            <gml:description>KIT FZK-Haus outer shell as constructions, storeys</gml:description>
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
                    <bldg:elevation>
                        <con:Elevation>
                            <con:elevationReference>lowestGroundPoint</con:elevationReference>
                            <con:elevationValue uomLabels="m">0</con:elevationValue>
                        </con:Elevation>
                    </bldg:elevation>
                    <bldg:sortKey>1</bldg:sortKey>
                    <bldg:buildingConstructiveElement>
                        <bldg:BuildingConstructiveElement>
                            <gml:name>001 - Ground Floor - Base Slab</gml:name>
                            <core:lod2Solid>
                                <gml:Solid>
                                    <gml:exterior>
                                        <gml:Shell>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_PG.mHelDj6PnYzKp3MnhVgl">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458912.0 5438785.0
                                                  113.5 458900.0 5438785.0 113.5 458900.0 5438795.0
                                                  113.5 458912.0 5438795.0 113.5 458912.0 5438785.0
                                                  113.5 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_PG.7FAPOy1jybU0TLzdG1Dm">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.0 5438785.0
                                                  113.7 458912.0 5438785.0 113.7 458912.0 5438795.0
                                                  113.7 458900.0 5438795.0 113.7 458900.0 5438785.0
                                                  113.7 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_PG.ceH8NdAk8Ttd8UQuOgDt">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_LR.FwrLjTkuh8XJbLagrufr">
                                                  <gml:posList srsDimension="3"> 458900.0 5438795.0
                                                  113.5 458900.0 5438795.0 113.7 458912.0 5438795.0
                                                  113.7 458912.0 5438795.0 113.5 458900.0 5438795.0
                                                  113.5 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_PG.ITGp0YBnXP8eXKUFZMsG">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_LR.bvJ7euyzF9Q7Ys21Wt79">
                                                  <gml:posList srsDimension="3"> 458912.0 5438795.0
                                                  113.5 458912.0 5438795.0 113.7 458912.0 5438785.0
                                                  113.7 458912.0 5438785.0 113.5 458912.0 5438795.0
                                                  113.5 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_PG.Cyq1iUxazmw3mD0RbodM">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_LR.EkTGtzaQLVXegi8az9su">
                                                  <gml:posList srsDimension="3"> 458912.0 5438785.0
                                                  113.5 458912.0 5438785.0 113.7 458900.0 5438785.0
                                                  113.7 458900.0 5438785.0 113.5 458912.0 5438785.0
                                                  113.5 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_PG.3iFLbThkrdFBOmkFhRg7">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_LR.G00iB4skiy5RVwAG2Dfi">
                                                  <gml:posList srsDimension="3"> 458900.0 5438785.0
                                                  113.5 458900.0 5438785.0 113.7 458900.0 5438795.0
                                                  113.7 458900.0 5438795.0 113.5 458900.0 5438785.0
                                                  113.5 </gml:posList>
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
                        <bldg:BuildingConstructiveElement>
                            <gml:name>002 - Wall - Ground Floor - North</gml:name>
                            <core:lod2Solid>
                                <gml:Solid>
                                    <gml:exterior>
                                        <gml:Shell>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_PG.gWwVgAuuS9Jxqtyj77Am">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.0 5438795.0
                                                  113.7 458900.3 5438794.7 113.7 458900.3 5438794.7
                                                  116.4 458900.0 5438795.0 116.4 458900.0 5438795.0
                                                  113.7 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_PG.owduZ7iEXmv5UO0vFTtz">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458911.7 5438794.7
                                                  113.7 458900.3 5438794.7 113.7 458900.0 5438795.0
                                                  113.7 458912.0 5438795.0 113.7 458911.7 5438794.7
                                                  113.7 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_PG.elv0WPN89ibJixa3FFlU">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.3 5438794.7
                                                  116.4 458911.7 5438794.7 116.4 458912.0 5438795.0
                                                  116.4 458900.0 5438795.0 116.4 458900.3 5438794.7
                                                  116.4 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_PG.jZ3CZ1UEOpvByerWczLi">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458911.7 5438794.7
                                                  113.7 458912.0 5438795.0 113.7 458912.0 5438795.0
                                                  116.4 458911.7 5438794.7 116.4 458911.7 5438794.7
                                                  113.7 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_PG.ewZe0Zhdr5uQltOo8z0F">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.3 5438794.7
                                                  116.4 458900.3 5438794.7 113.7 458911.7 5438794.7
                                                  113.7 458911.7 5438794.7 116.4 458900.3 5438794.7
                                                  116.4 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_PG.lpejwF7tMaS23mL1sezy">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_LR.ahXr6IXJAKjlmkaIAEv8">
                                                  <gml:posList srsDimension="3"> 458912.0 5438795.0
                                                  116.4 458912.0 5438795.0 113.7 458900.0 5438795.0
                                                  113.7 458900.0 5438795.0 116.4 458912.0 5438795.0
                                                  116.4 </gml:posList>
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
                        <bldg:BuildingConstructiveElement>
                            <gml:name>003 - Wall - Ground Floor - East</gml:name>
                            <core:lod2Solid>
                                <gml:Solid>
                                    <gml:exterior>
                                        <gml:Shell>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_PG.2ZNqf7TJxu0swpOv9XJa">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458911.7 5438794.7
                                                  113.7 458911.7 5438794.7 116.4 458912.0 5438795.0
                                                  116.4 458912.0 5438795.0 113.7 458911.7 5438794.7
                                                  113.7 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_PG.wGltm2VSJpXZBjaV6meC">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458911.7 5438785.3
                                                  113.7 458911.7 5438794.7 113.7 458912.0 5438795.0
                                                  113.7 458912.0 5438785.0 113.7 458911.7 5438785.3
                                                  113.7 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_PG.ypJzMfkWTPN5XFFAvN0C">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458911.7 5438794.7
                                                  116.4 458911.7 5438785.3 116.4 458912.0 5438785.0
                                                  116.4 458912.0 5438795.0 116.4 458911.7 5438794.7
                                                  116.4 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_PG.tssZNiYwsTN91vZ5X2Sf">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458911.7 5438785.3
                                                  113.7 458912.0 5438785.0 113.7 458912.0 5438785.0
                                                  116.4 458911.7 5438785.3 116.4 458911.7 5438785.3
                                                  113.7 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_PG.gqSSZnqSc5GH0uIftNVd">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458911.7 5438794.7
                                                  116.4 458911.7 5438794.7 113.7 458911.7 5438785.3
                                                  113.7 458911.7 5438785.3 116.4 458911.7 5438794.7
                                                  116.4 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_PG.PCa8ZVLePMvIZvD2K0IJ">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_LR.mmXVNAWndaKRRmZcHEJQ">
                                                  <gml:posList srsDimension="3"> 458912.0 5438785.0
                                                  116.4 458912.0 5438785.0 113.7 458912.0 5438795.0
                                                  113.7 458912.0 5438795.0 116.4 458912.0 5438785.0
                                                  116.4 </gml:posList>
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
                        <bldg:BuildingConstructiveElement>
                            <gml:name>004 - Wall - Ground Floor - South</gml:name>
                            <core:lod2Solid>
                                <gml:Solid>
                                    <gml:exterior>
                                        <gml:Shell>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_PG.ifGyd9g4FZRDuXwoq6Ke">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.3 5438785.3
                                                  113.7 458911.7 5438785.3 113.7 458912.0 5438785.0
                                                  113.7 458900.0 5438785.0 113.7 458900.3 5438785.3
                                                  113.7 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_PG.kg140CcG1bDYgQmvcsib">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458911.7 5438785.3
                                                  113.7 458911.7 5438785.3 116.4 458912.0 5438785.0
                                                  116.4 458912.0 5438785.0 113.7 458911.7 5438785.3
                                                  113.7 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_PG.MivRIPU9E444P5WI2p4a">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458911.7 5438785.3
                                                  116.4 458900.3 5438785.3 116.4 458900.0 5438785.0
                                                  116.4 458912.0 5438785.0 116.4 458911.7 5438785.3
                                                  116.4 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_PG.GW1iV0QvSekRkeQ7hnhI">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.0 5438785.0
                                                  113.7 458900.0 5438785.0 116.4 458900.3 5438785.3
                                                  116.4 458900.3 5438785.3 113.7 458900.0 5438785.0
                                                  113.7 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_PG.SFGNLgFY0veMHNPxLAkK">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458911.7 5438785.3
                                                  113.7 458900.3 5438785.3 113.7 458900.3 5438785.3
                                                  116.4 458911.7 5438785.3 116.4 458911.7 5438785.3
                                                  113.7 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_PG.P1SYTRPDAIPrQa6TqyRG">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_LR.QAS2JPANMFZ9X2VvBAn4">
                                                  <gml:posList srsDimension="3"> 458900.0 5438785.0
                                                  116.4 458900.0 5438785.0 113.7 458912.0 5438785.0
                                                  113.7 458912.0 5438785.0 116.4 458900.0 5438785.0
                                                  116.4 </gml:posList>
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
                        <bldg:BuildingConstructiveElement>
                            <gml:name>005 - Wall - Ground Floor - West</gml:name>
                            <core:lod2Solid>
                                <gml:Solid>
                                    <gml:exterior>
                                        <gml:Shell>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_PG.qHQckFloVzNwSvW411ni">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.0 5438785.0
                                                  113.7 458900.0 5438795.0 113.7 458900.3 5438794.7
                                                  113.7 458900.3 5438785.3 113.7 458900.0 5438785.0
                                                  113.7 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_PG.nCLnhtNhm0x0ke9joWIy">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.0 5438785.0
                                                  113.7 458900.3 5438785.3 113.7 458900.3 5438785.3
                                                  116.4 458900.0 5438785.0 116.4 458900.0 5438785.0
                                                  113.7 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_PG.ZnUbzWZlLZB7aCVbMpcc">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.3 5438785.3
                                                  116.4 458900.3 5438794.7 116.4 458900.0 5438795.0
                                                  116.4 458900.0 5438785.0 116.4 458900.3 5438785.3
                                                  116.4 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_PG.PTYhZ9oZcce0GOM9vqqD">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.0 5438795.0
                                                  113.7 458900.0 5438795.0 116.4 458900.3 5438794.7
                                                  116.4 458900.3 5438794.7 113.7 458900.0 5438795.0
                                                  113.7 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_PG.r1d4tZCkZUYYKkIzPii0">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.3 5438785.3
                                                  116.4 458900.3 5438785.3 113.7 458900.3 5438794.7
                                                  113.7 458900.3 5438794.7 116.4 458900.3 5438785.3
                                                  116.4 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_PG.cAeNp5WedYS0flA2LYuy">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_LR.s1EEETxoBUa0BbZyiR4Q">
                                                  <gml:posList srsDimension="3"> 458900.0 5438795.0
                                                  116.4 458900.0 5438795.0 113.7 458900.0 5438785.0
                                                  113.7 458900.0 5438785.0 116.4 458900.0 5438795.0
                                                  116.4 </gml:posList>
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
                </bldg:Storey>
            </bldg:buildingSubdivision>
            <bldg:buildingSubdivision>
                <bldg:Storey>
                    <gml:name>Second Floor</gml:name>
                    <bldg:class>non Entrance Floor</bldg:class>
                    <bldg:elevation>
                        <con:Elevation>
                            <con:elevationReference>lowestGroundPoint</con:elevationReference>
                            <con:elevationValue uomLabels="m">2.7</con:elevationValue>
                        </con:Elevation>
                    </bldg:elevation>
                    <bldg:sortKey>2</bldg:sortKey>
                    <bldg:buildingConstructiveElement>
                        <bldg:BuildingConstructiveElement>
                            <gml:name>006 - Second Floor - Roof - North</gml:name>
                            <core:lod2Solid>
                                <gml:Solid>
                                    <gml:exterior>
                                        <gml:Shell>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_PG.JFI5HAZdOd1KjCPReIi3">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_LR.hIsNLPmAIejVHthjJgdj">
                                                  <gml:posList srsDimension="3"> 458899.5 5438795.5
                                                  116.842265 458899.5 5438795.5 116.611325 458899.5
                                                  5438790.0 119.786751 458899.5 5438790.0 120.017691
                                                  458899.5 5438795.5 116.842265 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_PG.VsFPerMSZXAsMtKSP4xa">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_LR.GQMuOA6HG8oIbpQfnVdQ">
                                                  <gml:posList srsDimension="3"> 458912.5 5438795.5
                                                  116.842265 458912.5 5438795.5 116.611325 458899.5
                                                  5438795.5 116.611325 458899.5 5438795.5 116.842265
                                                  458912.5 5438795.5 116.842265 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_PG.mfDuaVSgyh6VMLfVm7qM">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_LR.xFanx8F8zWH7uDkXpB3T">
                                                  <gml:posList srsDimension="3"> 458912.5 5438790.0
                                                  120.017691 458912.5 5438790.0 119.786751 458912.5
                                                  5438795.5 116.611325 458912.5 5438795.5 116.842265
                                                  458912.5 5438790.0 120.017691 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_PG.364UX29qLii3IyXI0m1T">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_LR.L3YUwS8dwQrGISoB2wac">
                                                  <gml:posList srsDimension="3"> 458899.5 5438790.0
                                                  120.017691 458899.5 5438790.0 119.786751 458912.5
                                                  5438790.0 119.786751 458912.5 5438790.0 120.017691
                                                  458899.5 5438790.0 120.017691 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_PG.MO6YO8rZYBtGKC6ucsGa">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_LR.ENZR0cPivfmq1COBHaHg">
                                                  <gml:posList srsDimension="3"> 458912.5 5438795.5
                                                  116.611325 458912.5 5438790.0 119.786751 458899.5
                                                  5438790.0 119.786751 458899.5 5438795.5 116.611325
                                                  458912.5 5438795.5 116.611325 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_PG.AbmK7Q33A6vFNawva2nf">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_LR.JBXuDafRRC1yiNnpBcKr">
                                                  <gml:posList srsDimension="3"> 458912.5 5438790.0
                                                  120.017691 458912.5 5438795.5 116.842265 458899.5
                                                  5438795.5 116.842265 458899.5 5438790.0 120.017691
                                                  458912.5 5438790.0 120.017691 </gml:posList>
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
                        <bldg:BuildingConstructiveElement>
                            <gml:name>007 - Second Floor - Wall - East</gml:name>
                            <core:lod2Solid>
                                <gml:Solid>
                                    <gml:exterior>
                                        <gml:Shell>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.4g3FADqbqTKvBQqCDj6T">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458911.7 5438785.3
                                                  116.4 458911.7 5438794.7 116.4 458912.0 5438795.0
                                                  116.4 458912.0 5438785.0 116.4 458911.7 5438785.3
                                                  116.4 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.E9RQf8HkXkp5wmy0exAB">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458911.7 5438794.7
                                                  117.073205 458912.0 5438795.0 116.9 458912.0
                                                  5438795.0 116.4 458911.7 5438794.7 116.4 458911.7
                                                  5438794.7 117.073205 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.4hD7qUrewjxo7hrx8K0t">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458912.0 5438785.0
                                                  116.4 458912.0 5438785.0 116.9 458911.7 5438785.3
                                                  117.073205 458911.7 5438785.3 116.4 458912.0
                                                  5438785.0 116.4 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.NKutgXUzdZF0h9xGaHJy">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458912.0 5438790.0
                                                  119.786751 458912.0 5438795.0 116.9 458911.7
                                                  5438794.7 117.073205 458911.7 5438790.0 119.786751
                                                  458912.0 5438790.0 119.786751 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.KktjfVBU4e0sS4xaIyKY">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458911.7 5438790.0
                                                  119.786751 458911.7 5438785.3 117.073205 458912.0
                                                  5438785.0 116.9 458912.0 5438790.0 119.786751
                                                  458911.7 5438790.0 119.786751 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.tQqUkhToivgipr8dxPME">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458911.7 5438794.7
                                                  117.073205 458911.7 5438794.7 116.4 458911.7
                                                  5438785.3 116.4 458911.7 5438785.3 117.073205
                                                  458911.7 5438790.0 119.786751 458911.7 5438794.7
                                                  117.073205 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.cOMcY6d8PzJfEaPSVOg6">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_LR.ECpQqtgshzuFgz6EZTOp">
                                                  <gml:posList srsDimension="3"> 458912.0 5438795.0
                                                  116.4 458912.0 5438795.0 116.9 458912.0 5438790.0
                                                  119.786751 458912.0 5438785.0 116.9 458912.0
                                                  5438785.0 116.4 458912.0 5438795.0 116.4
                                                  </gml:posList>
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
                        <bldg:BuildingConstructiveElement>
                            <gml:name>008 - Second Floor - Wall - North</gml:name>
                            <core:lod2Solid>
                                <gml:Solid>
                                    <gml:exterior>
                                        <gml:Shell>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_PG.Ce418hEaaHOFPb4iN876">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458911.7 5438794.7
                                                  116.4 458900.3 5438794.7 116.4 458900.0 5438795.0
                                                  116.4 458912.0 5438795.0 116.4 458911.7 5438794.7
                                                  116.4 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_PG.hFVPrK4lM81wxERnmhyh">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.3 5438794.7
                                                  116.4 458900.3 5438794.7 117.073205 458900.0
                                                  5438795.0 116.9 458900.0 5438795.0 116.4 458900.3
                                                  5438794.7 116.4 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_PG.jhCJ3CvAc1zYnfNDpwmx">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458912.0 5438795.0
                                                  116.4 458912.0 5438795.0 116.9 458911.7 5438794.7
                                                  117.073205 458911.7 5438794.7 116.4 458912.0
                                                  5438795.0 116.4 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_PG.jpAdqfAe6kuJlv5hzRCE">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.3 5438794.7
                                                  117.073205 458911.7 5438794.7 117.073205 458912.0
                                                  5438795.0 116.9 458900.0 5438795.0 116.9 458900.3
                                                  5438794.7 117.073205 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_PG.YVW73hjJ4584aeAyGoz2">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458911.7 5438794.7
                                                  117.073205 458900.3 5438794.7 117.073205 458900.3
                                                  5438794.7 116.4 458911.7 5438794.7 116.4 458911.7
                                                  5438794.7 117.073205 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_PG.Moe1hG0ThUPVK5kz9siP">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_LR.pPixg2zvLexBUv0dtP1a">
                                                  <gml:posList srsDimension="3"> 458900.0 5438795.0
                                                  116.4 458900.0 5438795.0 116.9 458912.0 5438795.0
                                                  116.9 458912.0 5438795.0 116.4 458900.0 5438795.0
                                                  116.4 </gml:posList>
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
                        <bldg:BuildingConstructiveElement>
                            <gml:name>009 - Second Floor - Wall - South</gml:name>
                            <core:lod2Solid>
                                <gml:Solid>
                                    <gml:exterior>
                                        <gml:Shell>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_PG.3EezO5t4y14EvmJ5QU8n">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.3 5438785.3
                                                  116.4 458911.7 5438785.3 116.4 458912.0 5438785.0
                                                  116.4 458900.0 5438785.0 116.4 458900.3 5438785.3
                                                  116.4 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_PG.vECwnYVMzJst5uUcJKxW">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458911.7 5438785.3
                                                  117.073205 458912.0 5438785.0 116.9 458912.0
                                                  5438785.0 116.4 458911.7 5438785.3 116.4 458911.7
                                                  5438785.3 117.073205 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_PG.f02kdmSG98emcubRjzxM">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.0 5438785.0
                                                  116.9 458900.3 5438785.3 117.073205 458900.3
                                                  5438785.3 116.4 458900.0 5438785.0 116.4 458900.0
                                                  5438785.0 116.9 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_PG.HL4BoFVAuiDydWjJMwnz">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458911.7 5438785.3
                                                  117.073205 458900.3 5438785.3 117.073205 458900.0
                                                  5438785.0 116.9 458912.0 5438785.0 116.9 458911.7
                                                  5438785.3 117.073205 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_PG.6gLbwsUopOSdB2eVigw3">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.3 5438785.3
                                                  117.073205 458911.7 5438785.3 117.073205 458911.7
                                                  5438785.3 116.4 458900.3 5438785.3 116.4 458900.3
                                                  5438785.3 117.073205 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_PG.S8Gt0A6siUS60fNX7nHb">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_LR.ugJide10sDn9zh0GXLig">
                                                  <gml:posList srsDimension="3"> 458912.0 5438785.0
                                                  116.4 458912.0 5438785.0 116.9 458900.0 5438785.0
                                                  116.9 458900.0 5438785.0 116.4 458912.0 5438785.0
                                                  116.4 </gml:posList>
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
                        <bldg:BuildingConstructiveElement>
                            <gml:name>010 - Second Floor - Wall - West</gml:name>
                            <core:lod2Solid>
                                <gml:Solid>
                                    <gml:exterior>
                                        <gml:Shell>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.20llw7hJ7Am97eXuB24s">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.3 5438794.7
                                                  116.4 458900.3 5438785.3 116.4 458900.0 5438785.0
                                                  116.4 458900.0 5438795.0 116.4 458900.3 5438794.7
                                                  116.4 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.xjVOFfWI7EriovzaVPhG">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.3 5438785.3
                                                  116.4 458900.3 5438785.3 117.073205 458900.0
                                                  5438785.0 116.9 458900.0 5438785.0 116.4 458900.3
                                                  5438785.3 116.4 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.JSpRxWTNVqfUEFqCDrHA">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.0 5438795.0
                                                  116.9 458900.3 5438794.7 117.073205 458900.3
                                                  5438794.7 116.4 458900.0 5438795.0 116.4 458900.0
                                                  5438795.0 116.9 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.IqvSU6HnkDU5rIzWgWNY">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.0 5438785.0
                                                  116.9 458900.3 5438785.3 117.073205 458900.3
                                                  5438790.0 119.786751 458900.0 5438790.0 119.786751
                                                  458900.0 5438785.0 116.9 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.oSlslCAckMhsbEw4Kn1Z">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.3 5438790.0
                                                  119.786751 458900.3 5438794.7 117.073205 458900.0
                                                  5438795.0 116.9 458900.0 5438790.0 119.786751
                                                  458900.3 5438790.0 119.786751 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.1M1nBCVVwPNhPveLWYar">
                                                  <gml:exterior>
                                                  <gml:LinearRing>
                                                  <gml:posList srsDimension="3"> 458900.3 5438785.3
                                                  117.073205 458900.3 5438785.3 116.4 458900.3
                                                  5438794.7 116.4 458900.3 5438794.7 117.073205
                                                  458900.3 5438790.0 119.786751 458900.3 5438785.3
                                                  117.073205 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.QdQKcS9I1FWUogi2XBdN">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_LR.SrpVem0tdF2NKqQgEBfF">
                                                  <gml:posList srsDimension="3"> 458900.0 5438785.0
                                                  116.4 458900.0 5438785.0 116.9 458900.0 5438790.0
                                                  119.786751 458900.0 5438795.0 116.9 458900.0
                                                  5438795.0 116.4 458900.0 5438785.0 116.4
                                                  </gml:posList>
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
                        <bldg:BuildingConstructiveElement>
                            <gml:name>011 - Second Floor - Roof- South</gml:name>
                            <core:lod2Solid>
                                <gml:Solid>
                                    <gml:exterior>
                                        <gml:Shell>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_PG.5tzzcVjoycY7I7nsmccS">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_LR.Pmza3HXEoBax46G705rO">
                                                  <gml:posList srsDimension="3"> 458912.5 5438790.0
                                                  120.017691 458912.5 5438790.0 119.786751 458899.5
                                                  5438790.0 119.786751 458899.5 5438790.0 120.017691
                                                  458912.5 5438790.0 120.017691 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_PG.GPYoiBC32SVnd4C6xIZg">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_LR.i3aOFCYSIWU7C1JfU0My">
                                                  <gml:posList srsDimension="3"> 458912.5 5438784.5
                                                  116.842265 458912.5 5438784.5 116.611325 458912.5
                                                  5438790.0 119.786751 458912.5 5438790.0 120.017691
                                                  458912.5 5438784.5 116.842265 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_PG.9GGY9D4HJ0v68T24Fa8T">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_LR.Zy19NIWCd8kG3TFPQXCV">
                                                  <gml:posList srsDimension="3"> 458899.5 5438784.5
                                                  116.842265 458899.5 5438784.5 116.611325 458912.5
                                                  5438784.5 116.611325 458912.5 5438784.5 116.842265
                                                  458899.5 5438784.5 116.842265 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_PG.KnQkjTpc9jq7KHKjZO2E">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_LR.rNaI9FISsrEOCpUZB9P3">
                                                  <gml:posList srsDimension="3"> 458899.5 5438790.0
                                                  120.017691 458899.5 5438790.0 119.786751 458899.5
                                                  5438784.5 116.611325 458899.5 5438784.5 116.842265
                                                  458899.5 5438790.0 120.017691 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_PG.iu3zLZA723w4oWWx594N">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_LR.nOhi3GwspWGvNKohiXzD">
                                                  <gml:posList srsDimension="3"> 458912.5 5438784.5
                                                  116.611325 458899.5 5438784.5 116.611325 458899.5
                                                  5438790.0 119.786751 458912.5 5438790.0 119.786751
                                                  458912.5 5438784.5 116.611325 </gml:posList>
                                                  </gml:LinearRing>
                                                  </gml:exterior>
                                                </gml:Polygon>
                                            </gml:surfaceMember>
                                            <gml:surfaceMember>
                                                <gml:Polygon
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_PG.DXjiWLYFBUipOq3lzGI4">
                                                  <gml:exterior>
                                                  <gml:LinearRing
                                                  gml:id="_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_LR.L9N4hLe4qimFxc0RSQex">
                                                  <gml:posList srsDimension="3"> 458899.5 5438784.5
                                                  116.842265 458912.5 5438784.5 116.842265 458912.5
                                                  5438790.0 120.017691 458899.5 5438790.0 120.017691
                                                  458899.5 5438784.5 116.842265 </gml:posList>
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
                </bldg:Storey>
            </bldg:buildingSubdivision>
        </bldg:Building>
    </core:cityObjectMember>
    <core:appearanceMember>
        <app:Appearance>
            <app:surfaceData>
                <app:ParameterizedTexture>
                    <app:imageURI>textures/FZK-Haus-Back.png</app:imageURI>
                    <app:wrapMode>wrap</app:wrapMode>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_PG.ceH8NdAk8Ttd8UQuOgDt</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> 4.812742796881746e-16
                                        6.106226635438361e-16 4.812742796881746e-16
                                        0.055082762670476876 -0.9999999999999998
                                        0.055082762670476876 -0.9999999999999998
                                        6.106226635438361e-16 4.812742796881746e-16
                                        6.106226635438361e-16 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_LR.FwrLjTkuh8XJbLagrufr</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_PG.lpejwF7tMaS23mL1sezy</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> -0.9999999999999997 0.7987000537971238
                                        -0.9999999999999997 0.05508275569370144
                                        5.113539221686852e-16 0.05508275569370144
                                        5.113539221686852e-16 0.7987000537971238 -0.9999999999999997
                                        0.7987000537971238 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_LR.ahXr6IXJAKjlmkaIAEv8</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_PG.Moe1hG0ThUPVK5kz9siP</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> -4.967048506721028e-10
                                        0.7987000565293122 -4.967048506721028e-10 0.9364069611535101
                                        -1.0000000004967051 0.9364069611535101 -1.0000000004967051
                                        0.7987000565293122 -4.967048506721028e-10 0.7987000565293122 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_LR.pPixg2zvLexBUv0dtP1a</app:ring>
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
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_PG.ITGp0YBnXP8eXKUFZMsG</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> 1.0 -2.914335439641036e-16 1.0
                                        0.030685671783026273 0.0 0.030685671783026273 0.0
                                        -2.914335439641036e-16 1.0 -2.914335439641036e-16 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_LR.bvJ7euyzF9Q7Ys21Wt79</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_PG.PCa8ZVLePMvIZvD2K0IJ</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> 0.0 0.44494223811037215 0.0
                                        0.030685667896383145 1.0 0.030685667896383145 1.0
                                        0.44494223811037215 0.0 0.44494223811037215 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_LR.mmXVNAWndaKRRmZcHEJQ</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.cOMcY6d8PzJfEaPSVOg6</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> 1.0 0.44494222539546296 1.0
                                        0.5216564037098991 0.5000000000000896 0.964565929055548
                                        -8.881784197001253e-17 0.5216564037098991
                                        -8.881784197001253e-17 0.44494222539546296 1.0
                                        0.44494222539546296 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_LR.ECpQqtgshzuFgz6EZTOp</app:ring>
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
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_PG.Cyq1iUxazmw3mD0RbodM</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> 1.0 -6.938893903907228e-18 1.0
                                        0.05508276267047626 -1.2031856992204364e-16
                                        0.05508276267047626 -1.2031856992204364e-16
                                        -6.938893903907228e-18 1.0 -6.938893903907228e-18 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_LR.EkTGtzaQLVXegi8az9su</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_PG.P1SYTRPDAIPrQa6TqyRG</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> 0.0 0.7987000537971232 0.0
                                        0.05508275569370082 1.0000000000000002 0.05508275569370082
                                        1.0000000000000002 0.7987000537971232 0.0 0.7987000537971232 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_LR.QAS2JPANMFZ9X2VvBAn4</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_PG.S8Gt0A6siUS60fNX7nHb</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> 1.0000000000000002 0.798700040682076
                                        1.0000000000000002 0.9364069453062739 8.964432033456787e-26
                                        0.9364069453062739 8.964432033456787e-26 0.798700040682076
                                        1.0000000000000002 0.798700040682076 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_LR.ugJide10sDn9zh0GXLig</app:ring>
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
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_PG.3iFLbThkrdFBOmkFhRg7</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> 5.775291356258095e-16 0.0
                                        5.775291356258095e-16 0.03068567178302657
                                        -0.9999999999999994 0.03068567178302657 -0.9999999999999994
                                        0.0 5.775291356258095e-16 0.0 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_LR.G00iB4skiy5RVwAG2Dfi</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_PG.cAeNp5WedYS0flA2LYuy"</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> -0.9999999999999994 0.4449422381103724
                                        -0.9999999999999994 0.03068566789638344
                                        5.775291356258095e-16 0.03068566789638344
                                        5.775291356258095e-16 0.4449422381103724 -0.9999999999999994
                                        0.4449422381103724 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_LR.s1EEETxoBUa0BbZyiR4Q</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.QdQKcS9I1FWUogi2XBdN</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> 4.887112936773116e-16
                                        0.4449422253955035 4.887112936773116e-16 0.5216564037099396
                                        -0.5000000000000006 0.9645659290555887 -0.9999999999999994
                                        0.5216564037099396 -0.9999999999999994 0.4449422253955035
                                        4.887112936773116e-16 0.4449422253955035 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_LR.SrpVem0tdF2NKqQgEBfF</app:ring>
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
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_PG.JFI5HAZdOd1KjCPReIi3</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> 14.671668539650401 30.716597651817914
                                        15.029578339881674 30.438975359730012 15.029578339881676
                                        45.7082016923418 14.671668539650403 45.9858239844297
                                        14.671668539650401 30.716597651817914 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_LR.hIsNLPmAIejVHthjJgdj</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_PG.VsFPerMSZXAsMtKSP4xa</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> -8.59246889771538 30.71659765181792
                                        -8.59246889771538 30.161353067984578 14.671668539650405
                                        30.161353067984578 14.671668539650405 30.71659765181792
                                        -8.59246889771538 30.71659765181792 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_LR.GQMuOA6HG8oIbpQfnVdQ</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_PG.mfDuaVSgyh6VMLfVm7qM</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> -8.59246889771539 45.98582398442973
                                        -8.950378697946663 45.70820169234183 -8.950378697946661
                                        30.438975359730037 -8.592468897715388 30.716597651817942
                                        -8.59246889771539 45.98582398442973 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_LR.xFanx8F8zWH7uDkXpB3T</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_PG.364UX29qLii3IyXI0m1T</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> 14.671668539650407 45.98582398442973
                                        14.671668539650407 46.54106856826307 -8.592468897715381
                                        46.54106856826307 -8.592468897715381 45.98582398442973
                                        14.671668539650407 45.98582398442973 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_LR.L3YUwS8dwQrGISoB2wac</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_PG.MO6YO8rZYBtGKC6ucsGa</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> 36.14625694337267 30.438975359730012
                                        36.14625694337267 45.70820169234181 12.882119506006884
                                        45.70820169234181 12.882119506006884 30.438975359730012
                                        36.14625694337267 30.438975359730012 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_LR.ENZR0cPivfmq1COBHaHg</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_PG.AbmK7Q33A6vFNawva2nf</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> -8.59246889771538 45.985823984429715
                                        -8.59246889771538 30.716597651817917 14.671668539650405
                                        30.716597651817917 14.671668539650405 45.985823984429715
                                        -8.59246889771538 45.985823984429715 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_LR.JBXuDafRRC1yiNnpBcKr</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_PG.5tzzcVjoycY7I7nsmccS</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> 22.724639191048468 63.99140850690811
                                        22.724639191048468 63.43616392307516 45.988776628397524
                                        63.43616392307516 45.988776628397524 63.99140850690811
                                        22.724639191048468 63.99140850690811 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_LR.Pmza3HXEoBax46G705rO</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_PG.GPYoiBC32SVnd4C6xIZg</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> 12.882119506008985 56.35679533589367
                                        12.882119506008985 55.80155075206033 22.724639191048354
                                        63.43616392307505 22.724639191048354 63.99140850690839
                                        12.882119506008985 56.35679533589367 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_LR.i3aOFCYSIWU7C1JfU0My</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_PG.9GGY9D4HJ0v68T24Fa8T</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> 45.98877662839749 79.26063483950891
                                        45.98877662839749 79.81587942334185 22.72463919104845
                                        79.81587942334185 22.72463919104845 79.26063483950891
                                        45.98877662839749 79.26063483950891 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_LR.Zy19NIWCd8kG3TFPQXCV</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_PG.KnQkjTpc9jq7KHKjZO2E</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> 45.988776628397524 63.99140850690808
                                        46.34668642862854 64.26903079899579 46.346686428628544
                                        79.53825713159662 45.988776628397524 79.26063483950891
                                        45.988776628397524 63.99140850690808 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_LR.rNaI9FISsrEOCpUZB9P3</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_PG.iu3zLZA723w4oWWx594N</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> 22.724639191048443 79.8158794233419
                                        45.988776628397495 79.8158794233419 45.988776628397495
                                        95.08510575594272 22.724639191048443 95.08510575594272
                                        22.724639191048443 79.8158794233419 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_LR.nOhi3GwspWGvNKohiXzD</app:ring>
                                </app:TexCoordList>
                            </app:textureParameterization>
                        </app:TextureAssociation>
                    </app:textureParameterization>
                    <app:textureParameterization>
                        <app:TextureAssociation>
                            <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_PG.DXjiWLYFBUipOq3lzGI4</app:target>
                            <app:textureParameterization>
                                <app:TexCoordList>
                                    <app:textureCoordinates> 45.98877662839752 79.26063483950894
                                        22.724639191048464 79.26063483950894 22.724639191048464
                                        63.991408506908115 45.98877662839752 63.991408506908115
                                        45.98877662839752 79.26063483950894 </app:textureCoordinates>
                                    <app:ring>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_LR.L9N4hLe4qimFxc0RSQex</app:ring>
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
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_PG.mHelDj6PnYzKp3MnhVgl</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_PG.7FAPOy1jybU0TLzdG1Dm</app:target>
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
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_PG.gWwVgAuuS9Jxqtyj77Am</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_PG.owduZ7iEXmv5UO0vFTtz</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_PG.elv0WPN89ibJixa3FFlU</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_PG.jZ3CZ1UEOpvByerWczLi</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_PG.ewZe0Zhdr5uQltOo8z0F</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_PG.2ZNqf7TJxu0swpOv9XJa</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_PG.wGltm2VSJpXZBjaV6meC</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_PG.ypJzMfkWTPN5XFFAvN0C</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_PG.tssZNiYwsTN91vZ5X2Sf</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_PG.gqSSZnqSc5GH0uIftNVd</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_PG.ifGyd9g4FZRDuXwoq6Ke</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_PG.kg140CcG1bDYgQmvcsib</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_PG.MivRIPU9E444P5WI2p4a</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_PG.GW1iV0QvSekRkeQ7hnhI</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_PG.SFGNLgFY0veMHNPxLAkK</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_PG.qHQckFloVzNwSvW411ni</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_PG.nCLnhtNhm0x0ke9joWIy</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_PG.ZnUbzWZlLZB7aCVbMpcc</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_PG.PTYhZ9oZcce0GOM9vqqD</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_PG.r1d4tZCkZUYYKkIzPii0</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.4g3FADqbqTKvBQqCDj6T</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.E9RQf8HkXkp5wmy0exAB</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.4hD7qUrewjxo7hrx8K0t</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.NKutgXUzdZF0h9xGaHJy</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.KktjfVBU4e0sS4xaIyKY</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.tQqUkhToivgipr8dxPME</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_PG.Ce418hEaaHOFPb4iN876</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_PG.hFVPrK4lM81wxERnmhyh</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_PG.jhCJ3CvAc1zYnfNDpwmx</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_PG.jpAdqfAe6kuJlv5hzRCE</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_PG.YVW73hjJ4584aeAyGoz2</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_PG.3EezO5t4y14EvmJ5QU8n</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_PG.vECwnYVMzJst5uUcJKxW</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_PG.f02kdmSG98emcubRjzxM</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_PG.HL4BoFVAuiDydWjJMwnz</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_PG.6gLbwsUopOSdB2eVigw3</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.20llw7hJ7Am97eXuB24s</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.xjVOFfWI7EriovzaVPhG</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.JSpRxWTNVqfUEFqCDrHA</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.IqvSU6HnkDU5rIzWgWNY</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.oSlslCAckMhsbEw4Kn1Z</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.1M1nBCVVwPNhPveLWYar</app:target>
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
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_PG.mHelDj6PnYzKp3MnhVgl</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_PG.7FAPOy1jybU0TLzdG1Dm</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_PG.ceH8NdAk8Ttd8UQuOgDt</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_PG.ITGp0YBnXP8eXKUFZMsG</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_PG.Cyq1iUxazmw3mD0RbodM</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.RWfOL7hfvGrCRMRbM7tj_PG.3iFLbThkrdFBOmkFhRg7</app:target>
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
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_PG.gWwVgAuuS9Jxqtyj77Am</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_PG.owduZ7iEXmv5UO0vFTtz</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_PG.elv0WPN89ibJixa3FFlU</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_PG.jZ3CZ1UEOpvByerWczLi</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_PG.ewZe0Zhdr5uQltOo8z0F</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.7QMYhL4lbWZvbusLqVCH_PG.lpejwF7tMaS23mL1sezy</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_PG.2ZNqf7TJxu0swpOv9XJa</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_PG.wGltm2VSJpXZBjaV6meC</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_PG.ypJzMfkWTPN5XFFAvN0C</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_PG.tssZNiYwsTN91vZ5X2Sf</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_PG.gqSSZnqSc5GH0uIftNVd</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.3BrHkWC6Oo4foNqE8hFa_PG.PCa8ZVLePMvIZvD2K0IJ</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_PG.ifGyd9g4FZRDuXwoq6Ke</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_PG.kg140CcG1bDYgQmvcsib</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_PG.MivRIPU9E444P5WI2p4a</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_PG.GW1iV0QvSekRkeQ7hnhI</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_PG.SFGNLgFY0veMHNPxLAkK</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.fDTUZtUyGJ7txIS3FZmY_PG.P1SYTRPDAIPrQa6TqyRG</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_PG.qHQckFloVzNwSvW411ni</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_PG.nCLnhtNhm0x0ke9joWIy</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_PG.ZnUbzWZlLZB7aCVbMpcc</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_PG.PTYhZ9oZcce0GOM9vqqD</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_PG.r1d4tZCkZUYYKkIzPii0</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.YUcS8CC7RNT5ZVegqop7_PG.cAeNp5WedYS0flA2LYuy</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.4g3FADqbqTKvBQqCDj6T</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.E9RQf8HkXkp5wmy0exAB</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.4hD7qUrewjxo7hrx8K0t</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.NKutgXUzdZF0h9xGaHJy</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.KktjfVBU4e0sS4xaIyKY</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.tQqUkhToivgipr8dxPME</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.XaHLYXueuU0wO9KrcTrK_PG.cOMcY6d8PzJfEaPSVOg6</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_PG.Ce418hEaaHOFPb4iN876</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_PG.hFVPrK4lM81wxERnmhyh</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_PG.jhCJ3CvAc1zYnfNDpwmx</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_PG.jpAdqfAe6kuJlv5hzRCE</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_PG.YVW73hjJ4584aeAyGoz2</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.jPpc9BSf36SjKk1hHJJZ_PG.Moe1hG0ThUPVK5kz9siP</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_PG.3EezO5t4y14EvmJ5QU8n</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_PG.vECwnYVMzJst5uUcJKxW</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_PG.f02kdmSG98emcubRjzxM</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_PG.HL4BoFVAuiDydWjJMwnz</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_PG.6gLbwsUopOSdB2eVigw3</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.g94Zjbs4DRjqUw623ECU_PG.S8Gt0A6siUS60fNX7nHb</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.20llw7hJ7Am97eXuB24s</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.xjVOFfWI7EriovzaVPhG</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.JSpRxWTNVqfUEFqCDrHA</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.IqvSU6HnkDU5rIzWgWNY</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.oSlslCAckMhsbEw4Kn1Z</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.1M1nBCVVwPNhPveLWYar</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.NYtdoUJRyiMffRVeIcDR_PG.QdQKcS9I1FWUogi2XBdN</app:target>
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
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_PG.JFI5HAZdOd1KjCPReIi3</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_PG.VsFPerMSZXAsMtKSP4xa</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_PG.mfDuaVSgyh6VMLfVm7qM</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_PG.364UX29qLii3IyXI0m1T</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_PG.MO6YO8rZYBtGKC6ucsGa</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.uBsrBvpGXi9RPwurWsHs_PG.AbmK7Q33A6vFNawva2nf</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_PG.5tzzcVjoycY7I7nsmccS</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_PG.GPYoiBC32SVnd4C6xIZg</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_PG.9GGY9D4HJ0v68T24Fa8T</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_PG.KnQkjTpc9jq7KHKjZO2E</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_PG.iu3zLZA723w4oWWx594N</app:target>
                    <app:target>#_FZK-Haus-Storey-Construction-tex_BD.JCU7MzB2Car2JgvvpGrV_BP.F7n5Sg4BTpOmE3l4gCdb_PG.DXjiWLYFBUipOq3lzGI4</app:target>
                </app:X3DMaterial>
            </app:surfaceData>
        </app:Appearance>
    </core:appearanceMember>
</core:CityModel>
