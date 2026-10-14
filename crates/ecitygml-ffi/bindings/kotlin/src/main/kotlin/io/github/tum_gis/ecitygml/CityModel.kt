package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface CityModelLib: Library {
    fun ecitygml_CityModel_destroy(handle: Pointer)
    fun ecitygml_CityModel_id(handle: Pointer): Pointer?
    fun ecitygml_CityModel_names(handle: Pointer): Pointer
    fun ecitygml_CityModel_bounded_by(handle: Pointer): Pointer?
    fun ecitygml_CityModel_feature_id(handle: Pointer): Pointer
    fun ecitygml_CityModel_creation_date(handle: Pointer): Pointer?
    fun ecitygml_CityModel_termination_date(handle: Pointer): Pointer?
    fun ecitygml_CityModel_valid_from(handle: Pointer): Pointer?
    fun ecitygml_CityModel_valid_to(handle: Pointer): Pointer?
    fun ecitygml_CityModel_apply_translation(handle: Pointer, vector: Vector3Native): Unit
    fun ecitygml_CityModel_apply_scale(handle: Pointer, scale: Scale3Native): Unit
    fun ecitygml_CityModel_iter_features(handle: Pointer): Pointer
    fun ecitygml_CityModel_iter_city_objects(handle: Pointer): Pointer
    fun ecitygml_CityModel_city_object_members(handle: Pointer): Pointer
    fun ecitygml_CityModel_recompute_child_bounding_shapes(handle: Pointer): Unit
    fun ecitygml_CityModel_city_objects_len(handle: Pointer): FFISizet
}
/** A city model; mutable for `recompute_child_bounding_shapes`, `apply_translation` and `apply_scale`.
*/
class CityModel internal constructor (
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

    private class CityModelCleaner(val handle: Pointer, val lib: CityModelLib) : Runnable {
        override fun run() {
            lib.ecitygml_CityModel_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, CityModel.CityModelCleaner(handle, CityModel.lib));
    }

    companion object {
        internal val libClass: Class<CityModelLib> = CityModelLib::class.java
        internal val lib: CityModelLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityModel_id(handle);
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
        
        val returnVal = lib.ecitygml_CityModel_names(handle);
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
        
        val returnVal = lib.ecitygml_CityModel_bounded_by(handle);
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
        
        val returnVal = lib.ecitygml_CityModel_feature_id(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Id(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun creationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityModel_creation_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun terminationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityModel_termination_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validFrom(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityModel_valid_from(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validTo(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityModel_valid_to(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    /** Translates the geometry and every stored envelope by `vector` (Rust:
    *`ApplyTransform::apply_translation`).
    */
    fun applyTranslation(vector: Vector3): Unit {
        
        val returnVal = lib.ecitygml_CityModel_apply_translation(handle, vector.toNative());
        
    }
    
    /** Scales the geometry and every stored envelope by `scale`, per axis and about the origin (Rust:
    *`ApplyTransform::apply_scale`).
    */
    fun applyScale(scale: Scale3): Unit {
        
        val returnVal = lib.ecitygml_CityModel_apply_scale(handle, scale.toNative());
        
    }
    
    /** Lazily iterates over all features at any depth (Rust: `IterFeatures::iter_features`).
    */
    fun iterFeatures(): AbstractFeatureKindRefIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityModel_iter_features(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = AbstractFeatureKindRefIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** Lazily iterates over all city objects at any depth, without the city model itself (Rust:
    *`iter_city_objects`).
    */
    fun iterCityObjects(): AbstractCityObjectKindRefIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityModel_iter_city_objects(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = AbstractCityObjectKindRefIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** The direct `cityObjectMember`s (Rust: `city_object_members`).
    */
    fun cityObjectMembers(): AbstractCityObjectPropertyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityModel_city_object_members(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = AbstractCityObjectPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** Recomputes the bounding shape of every feature below the city model from its geometry.
    */
    fun recomputeChildBoundingShapes(): Unit {
        
        val returnVal = lib.ecitygml_CityModel_recompute_child_bounding_shapes(handle);
        
    }
    
    /** Number of direct `cityObjectMember`s.
    */
    fun cityObjectsLen(): ULong {
        
        val returnVal = lib.ecitygml_CityModel_city_objects_len(handle);
        return (returnVal.toULong())
    }

}