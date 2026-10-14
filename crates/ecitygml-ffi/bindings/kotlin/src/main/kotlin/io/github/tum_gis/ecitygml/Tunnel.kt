package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TunnelLib: Library {
    fun ecitygml_Tunnel_destroy(handle: Pointer)
    fun ecitygml_Tunnel_id(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_names(handle: Pointer): Pointer
    fun ecitygml_Tunnel_bounded_by(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_feature_id(handle: Pointer): Pointer
    fun ecitygml_Tunnel_creation_date(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_termination_date(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_valid_from(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_valid_to(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_relative_to_terrain(handle: Pointer): OptionInt
    fun ecitygml_Tunnel_relative_to_water(handle: Pointer): OptionInt
    fun ecitygml_Tunnel_external_references(handle: Pointer): Pointer
    fun ecitygml_Tunnel_generic_attributes(handle: Pointer): Pointer
    fun ecitygml_Tunnel_related_to(handle: Pointer): Pointer
    fun ecitygml_Tunnel_space_type(handle: Pointer): OptionInt
    fun ecitygml_Tunnel_lod1_solid(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_lod2_solid(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_lod3_solid(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_lod0_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_lod2_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_lod3_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_lod0_multi_curve(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_lod2_multi_curve(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_lod3_multi_curve(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_lod0_point(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_boundaries(handle: Pointer): Pointer
    fun ecitygml_Tunnel_lod1_terrain_intersection_curve(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_lod2_terrain_intersection_curve(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_lod3_terrain_intersection_curve(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_lod1_implicit_representation(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_lod2_implicit_representation(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_lod3_implicit_representation(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_date_of_construction(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_date_of_demolition(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_heights(handle: Pointer): Pointer
    fun ecitygml_Tunnel_occupancies(handle: Pointer): Pointer
    fun ecitygml_Tunnel_class(handle: Pointer): Pointer?
    fun ecitygml_Tunnel_functions(handle: Pointer): Pointer
    fun ecitygml_Tunnel_usages(handle: Pointer): Pointer
    fun ecitygml_Tunnel_try_from(feature: Pointer): Pointer?
    fun ecitygml_Tunnel_tunnel_parts(handle: Pointer): Pointer
}
/** A tunnel, borrowed from a city model.
*/
class Tunnel internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal var owned: Boolean,
)  {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class TunnelCleaner(val handle: Pointer, val lib: TunnelLib) : Runnable {
        override fun run() {
            lib.ecitygml_Tunnel_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Tunnel.TunnelCleaner(handle, Tunnel.lib));
    }

    companion object {
        internal val libClass: Class<TunnelLib> = TunnelLib::class.java
        internal val lib: TunnelLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The feature as a tunnel, or none if it is another type (Rust: `<&Tunnel>::try_from`).
        */
        fun tryFrom(feature: AbstractFeatureKindRef): Tunnel? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(feature);
            
            val returnVal = lib.ecitygml_Tunnel_try_from(feature.handle);
            val selfEdges: List<Any> = listOf(feature)
            val handle = returnVal ?: return null
            val returnOpaque = Tunnel(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_id(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Id(handle, selfEdges, false)
        return returnOpaque
    }
    
    /** The object's `gml:name`s.
    */
    fun names(): CodeIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_names(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CodeIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** The feature's bounding shape (`gml:boundedBy`), if it has one.
    */
    fun boundedBy(): BoundingShape? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_bounded_by(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = BoundingShape(handle, selfEdges, false)
        return returnOpaque
    }
    
    /** The feature's `gml:id`.
    */
    fun featureId(): Id {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_feature_id(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Id(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun creationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_creation_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun terminationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_termination_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validFrom(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_valid_from(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validTo(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_valid_to(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun relativeToTerrain(): RelativeToTerrain? {
        
        val returnVal = lib.ecitygml_Tunnel_relative_to_terrain(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToTerrain.fromNative(intermediateOption)
    }
    
    fun relativeToWater(): RelativeToWater? {
        
        val returnVal = lib.ecitygml_Tunnel_relative_to_water(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToWater.fromNative(intermediateOption)
    }
    
    fun externalReferences(): ExternalReferenceIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_external_references(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = ExternalReferenceIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun genericAttributes(): GenericAttributeKindIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_generic_attributes(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = GenericAttributeKindIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** Relations to other city objects (`relatedTo`).
    */
    fun relatedTo(): CityObjectRelationPropertyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_related_to(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CityObjectRelationPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun spaceType(): SpaceType? {
        
        val returnVal = lib.ecitygml_Tunnel_space_type(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return SpaceType.fromNative(intermediateOption)
    }
    
    fun lod1Solid(): SolidProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_lod1_solid(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SolidProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2Solid(): SolidProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_lod2_solid(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SolidProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3Solid(): SolidProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_lod3_solid(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SolidProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod0MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_lod0_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_lod2_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_lod3_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod0MultiCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_lod0_multi_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2MultiCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_lod2_multi_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3MultiCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_lod3_multi_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod0Point(): PointProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_lod0_point(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = PointProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    /** The space's boundaries (e.g. wall surfaces or traffic areas).
    */
    fun boundaries(): AbstractSpaceBoundaryPropertyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_boundaries(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = AbstractSpaceBoundaryPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun lod1TerrainIntersectionCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_lod1_terrain_intersection_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2TerrainIntersectionCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_lod2_terrain_intersection_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3TerrainIntersectionCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_lod3_terrain_intersection_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod1ImplicitRepresentation(): ImplicitGeometryProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_lod1_implicit_representation(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = ImplicitGeometryProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2ImplicitRepresentation(): ImplicitGeometryProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_lod2_implicit_representation(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = ImplicitGeometryProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3ImplicitRepresentation(): ImplicitGeometryProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_lod3_implicit_representation(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = ImplicitGeometryProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun dateOfConstruction(): Date? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_date_of_construction(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Date(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun dateOfDemolition(): Date? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_date_of_demolition(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Date(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun heights(): HeightIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_heights(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = HeightIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun occupancies(): OccupancyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_occupancies(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = OccupancyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun class_(): TunnelClassValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_class(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = TunnelClassValue(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun functions(): TunnelFunctionValueIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_functions(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = TunnelFunctionValueIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun usages(): TunnelUsageValueIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_usages(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = TunnelUsageValueIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun tunnelParts(): TunnelPartPropertyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Tunnel_tunnel_parts(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = TunnelPartPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }

}