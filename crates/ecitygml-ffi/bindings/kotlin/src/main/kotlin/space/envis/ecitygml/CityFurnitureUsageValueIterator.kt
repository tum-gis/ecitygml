package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface CityFurnitureUsageValueIteratorLib: Library {
    fun ecitygml_CityFurnitureUsageValueIterator_destroy(handle: Pointer)
    fun ecitygml_CityFurnitureUsageValueIterator_next(handle: Pointer): Pointer?
}
typealias CityFurnitureUsageValueIteratorIteratorItem = CityFurnitureUsageValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class CityFurnitureUsageValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<CityFurnitureUsageValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class CityFurnitureUsageValueIteratorCleaner(val handle: Pointer, val lib: CityFurnitureUsageValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_CityFurnitureUsageValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, CityFurnitureUsageValueIterator.CityFurnitureUsageValueIteratorCleaner(handle, CityFurnitureUsageValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<CityFurnitureUsageValueIteratorLib> = CityFurnitureUsageValueIteratorLib::class.java
        internal val lib: CityFurnitureUsageValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): CityFurnitureUsageValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityFurnitureUsageValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = CityFurnitureUsageValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): CityFurnitureUsageValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}