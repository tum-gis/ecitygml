package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractCityObjectKindRefLib: Library {
    fun ecitygml_AbstractCityObjectKindRef_destroy(handle: Pointer)
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
    }
    
    fun featureType(): FeatureType {
        
        val returnVal = lib.ecitygml_AbstractCityObjectKindRef_feature_type(handle);
        return (FeatureType.fromNative(returnVal))
    }

}