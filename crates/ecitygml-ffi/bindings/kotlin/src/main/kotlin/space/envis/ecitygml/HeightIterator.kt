package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface HeightIteratorLib: Library {
    fun ecitygml_HeightIterator_destroy(handle: Pointer)
    fun ecitygml_HeightIterator_next(handle: Pointer): Pointer?
}
typealias HeightIteratorIteratorItem = Height?
/** Iterates over heights, borrowed from a city model.
*/
class HeightIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<Height?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class HeightIteratorCleaner(val handle: Pointer, val lib: HeightIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_HeightIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, HeightIterator.HeightIteratorCleaner(handle, HeightIterator.lib));
    }

    companion object {
        internal val libClass: Class<HeightIteratorLib> = HeightIteratorLib::class.java
        internal val lib: HeightIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): Height? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_HeightIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Height(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): Height?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}