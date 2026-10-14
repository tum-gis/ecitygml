package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractCityObjectPropertyLib: Library {
    fun ecitygml_AbstractCityObjectProperty_destroy(handle: Pointer)
    fun ecitygml_AbstractCityObjectProperty_object(handle: Pointer): Pointer?
    fun ecitygml_AbstractCityObjectProperty_href(handle: Pointer): Pointer?
}
/** A city object property (inline city object and/or `xlink:href`), borrowed from a city model.
*/
class AbstractCityObjectProperty internal constructor (
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

    private class AbstractCityObjectPropertyCleaner(val handle: Pointer, val lib: AbstractCityObjectPropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractCityObjectProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractCityObjectProperty.AbstractCityObjectPropertyCleaner(handle, AbstractCityObjectProperty.lib));
    }

    companion object {
        internal val libClass: Class<AbstractCityObjectPropertyLib> = AbstractCityObjectPropertyLib::class.java
        internal val lib: AbstractCityObjectPropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline city object; none if the property only references one via `href`.
    */
    fun object_(): AbstractCityObjectKind? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractCityObjectProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractCityObjectKind(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractCityObjectProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}