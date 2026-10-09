package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface CityObjectRelationPropertyIteratorLib: Library {
    fun ecitygml_CityObjectRelationPropertyIterator_destroy(handle: Pointer)
    fun ecitygml_CityObjectRelationPropertyIterator_next(handle: Pointer): Pointer?
}
typealias CityObjectRelationPropertyIteratorIteratorItem = CityObjectRelationProperty?
/** Iterates over city object relation properties, borrowed from a city model.
*/
class CityObjectRelationPropertyIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<CityObjectRelationProperty?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class CityObjectRelationPropertyIteratorCleaner(val handle: Pointer, val lib: CityObjectRelationPropertyIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_CityObjectRelationPropertyIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, CityObjectRelationPropertyIterator.CityObjectRelationPropertyIteratorCleaner(handle, CityObjectRelationPropertyIterator.lib));
    }

    companion object {
        internal val libClass: Class<CityObjectRelationPropertyIteratorLib> = CityObjectRelationPropertyIteratorLib::class.java
        internal val lib: CityObjectRelationPropertyIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): CityObjectRelationProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityObjectRelationPropertyIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = CityObjectRelationProperty(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): CityObjectRelationProperty?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}