package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AuxiliaryTrafficAreaFunctionValueIteratorLib: Library {
    fun ecitygml_AuxiliaryTrafficAreaFunctionValueIterator_destroy(handle: Pointer)
    fun ecitygml_AuxiliaryTrafficAreaFunctionValueIterator_next(handle: Pointer): Pointer?
}
typealias AuxiliaryTrafficAreaFunctionValueIteratorIteratorItem = AuxiliaryTrafficAreaFunctionValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class AuxiliaryTrafficAreaFunctionValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<AuxiliaryTrafficAreaFunctionValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class AuxiliaryTrafficAreaFunctionValueIteratorCleaner(val handle: Pointer, val lib: AuxiliaryTrafficAreaFunctionValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_AuxiliaryTrafficAreaFunctionValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AuxiliaryTrafficAreaFunctionValueIterator.AuxiliaryTrafficAreaFunctionValueIteratorCleaner(handle, AuxiliaryTrafficAreaFunctionValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<AuxiliaryTrafficAreaFunctionValueIteratorLib> = AuxiliaryTrafficAreaFunctionValueIteratorLib::class.java
        internal val lib: AuxiliaryTrafficAreaFunctionValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): AuxiliaryTrafficAreaFunctionValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficAreaFunctionValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AuxiliaryTrafficAreaFunctionValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): AuxiliaryTrafficAreaFunctionValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}