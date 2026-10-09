package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface ShellIteratorLib: Library {
    fun ecitygml_ShellIterator_destroy(handle: Pointer)
    fun ecitygml_ShellIterator_next(handle: Pointer): Pointer?
}
typealias ShellIteratorIteratorItem = Shell?
/** Iterates over shells (e.g. a solid's interior shells), borrowed from a city model.
*/
class ShellIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<Shell?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class ShellIteratorCleaner(val handle: Pointer, val lib: ShellIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_ShellIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, ShellIterator.ShellIteratorCleaner(handle, ShellIterator.lib));
    }

    companion object {
        internal val libClass: Class<ShellIteratorLib> = ShellIteratorLib::class.java
        internal val lib: ShellIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): Shell? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ShellIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Shell(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): Shell?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}