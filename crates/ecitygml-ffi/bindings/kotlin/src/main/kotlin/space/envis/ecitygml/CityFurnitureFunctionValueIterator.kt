package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface CityFurnitureFunctionValueIteratorLib: Library {
    fun ecitygml_CityFurnitureFunctionValueIterator_destroy(handle: Pointer)
    fun ecitygml_CityFurnitureFunctionValueIterator_next(handle: Pointer): Pointer?
}
typealias CityFurnitureFunctionValueIteratorIteratorItem = CityFurnitureFunctionValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class CityFurnitureFunctionValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<CityFurnitureFunctionValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class CityFurnitureFunctionValueIteratorCleaner(val handle: Pointer, val lib: CityFurnitureFunctionValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_CityFurnitureFunctionValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, CityFurnitureFunctionValueIterator.CityFurnitureFunctionValueIteratorCleaner(handle, CityFurnitureFunctionValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<CityFurnitureFunctionValueIteratorLib> = CityFurnitureFunctionValueIteratorLib::class.java
        internal val lib: CityFurnitureFunctionValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): CityFurnitureFunctionValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityFurnitureFunctionValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = CityFurnitureFunctionValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): CityFurnitureFunctionValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}