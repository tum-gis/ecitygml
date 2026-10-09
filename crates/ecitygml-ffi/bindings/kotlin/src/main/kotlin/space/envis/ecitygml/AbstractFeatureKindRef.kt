package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractFeatureKindRefLib: Library {
    fun ecitygml_AbstractFeatureKindRef_destroy(handle: Pointer)
    fun ecitygml_AbstractFeatureKindRef_from_space_boundary(boundary: Pointer): Pointer
    fun ecitygml_AbstractFeatureKindRef_from_city_object(cityObject: Pointer): Pointer
    fun ecitygml_AbstractFeatureKindRef_feature_type(handle: Pointer): Int
}
/** A reference to a feature of any type; convert it with e.g. `TrafficSpace::try_from`.
*/
class AbstractFeatureKindRef internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
)  {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class AbstractFeatureKindRefCleaner(val handle: Pointer, val lib: AbstractFeatureKindRefLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractFeatureKindRef_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractFeatureKindRef.AbstractFeatureKindRefCleaner(handle, AbstractFeatureKindRef.lib));
    }

    companion object {
        internal val libClass: Class<AbstractFeatureKindRefLib> = AbstractFeatureKindRefLib::class.java
        internal val lib: AbstractFeatureKindRefLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The feature a space boundary is (Rust: `From<&AbstractSpaceBoundaryKind>`), to convert it
        *with e.g. `WallSurface::try_from`.
        */
        fun fromSpaceBoundary(boundary: AbstractSpaceBoundaryKind): AbstractFeatureKindRef {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(boundary);
            
            val returnVal = lib.ecitygml_AbstractFeatureKindRef_from_space_boundary(boundary.handle);
            val selfEdges: List<Any> = listOf()
            val handle = returnVal 
            val returnOpaque = AbstractFeatureKindRef(handle, selfEdges, aEdges, true)
            return returnOpaque
        }
        @JvmStatic
        
        /** The feature a city object is, to convert it with e.g. `Building::try_from` (Rust wraps it in
        *the `AbstractFeatureWithLifespanKind(AbstractCityObjectKind(_))` variants; it has no `From`).
        */
        fun fromCityObject(cityObject: AbstractCityObjectKindRef): AbstractFeatureKindRef {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(cityObject);
            
            val returnVal = lib.ecitygml_AbstractFeatureKindRef_from_city_object(cityObject.handle);
            val selfEdges: List<Any> = listOf()
            val handle = returnVal 
            val returnOpaque = AbstractFeatureKindRef(handle, selfEdges, aEdges, true)
            return returnOpaque
        }
    }
    
    fun featureType(): FeatureType {
        
        val returnVal = lib.ecitygml_AbstractFeatureKindRef_feature_type(handle);
        return (FeatureType.fromNative(returnVal))
    }

}