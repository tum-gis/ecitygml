package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractCityObjectKindRefLib: Library {
    fun ecitygml_AbstractCityObjectKindRef_destroy(handle: Pointer)
    fun ecitygml_AbstractCityObjectKindRef_from_city_object(cityObject: Pointer): Pointer
    fun ecitygml_AbstractCityObjectKindRef_feature_type(handle: Pointer): Int
}
/** A reference to a city object of any type; convert it with
*`AbstractFeatureKindRef::from_city_object` and then e.g. `Building::try_from`.
*/
class AbstractCityObjectKindRef internal constructor (
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

    private class AbstractCityObjectKindRefCleaner(val handle: Pointer, val lib: AbstractCityObjectKindRefLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractCityObjectKindRef_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractCityObjectKindRef.AbstractCityObjectKindRefCleaner(handle, AbstractCityObjectKindRef.lib));
    }

    companion object {
        internal val libClass: Class<AbstractCityObjectKindRefLib> = AbstractCityObjectKindRefLib::class.java
        internal val lib: AbstractCityObjectKindRefLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** A reference to a city object (Rust: `From<&AbstractCityObjectKind>`), to convert it with
        *`AbstractFeatureKindRef::from_city_object` and then e.g. `Building::try_from`.
        */
        fun fromCityObject(cityObject: AbstractCityObjectKind): AbstractCityObjectKindRef {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(cityObject);
            
            val returnVal = lib.ecitygml_AbstractCityObjectKindRef_from_city_object(cityObject.handle);
            val selfEdges: List<Any> = listOf()
            val handle = returnVal 
            val returnOpaque = AbstractCityObjectKindRef(handle, selfEdges, aEdges, true)
            return returnOpaque
        }
    }
    
    fun featureType(): FeatureType {
        
        val returnVal = lib.ecitygml_AbstractCityObjectKindRef_feature_type(handle);
        return (FeatureType.fromNative(returnVal))
    }

}