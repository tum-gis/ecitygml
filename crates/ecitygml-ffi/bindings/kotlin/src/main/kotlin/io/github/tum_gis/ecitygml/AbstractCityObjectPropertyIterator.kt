package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractCityObjectPropertyIteratorLib: Library {
    fun ecitygml_AbstractCityObjectPropertyIterator_destroy(handle: Pointer)
    fun ecitygml_AbstractCityObjectPropertyIterator_next(handle: Pointer): Pointer?
}
typealias AbstractCityObjectPropertyIteratorIteratorItem = AbstractCityObjectProperty?
/** Iterates over city object properties, borrowed from a city model.
*/
class AbstractCityObjectPropertyIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<AbstractCityObjectProperty?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class AbstractCityObjectPropertyIteratorCleaner(val handle: Pointer, val lib: AbstractCityObjectPropertyIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractCityObjectPropertyIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractCityObjectPropertyIterator.AbstractCityObjectPropertyIteratorCleaner(handle, AbstractCityObjectPropertyIterator.lib));
    }

    companion object {
        internal val libClass: Class<AbstractCityObjectPropertyIteratorLib> = AbstractCityObjectPropertyIteratorLib::class.java
        internal val lib: AbstractCityObjectPropertyIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): AbstractCityObjectProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractCityObjectPropertyIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractCityObjectProperty(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): AbstractCityObjectProperty?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}