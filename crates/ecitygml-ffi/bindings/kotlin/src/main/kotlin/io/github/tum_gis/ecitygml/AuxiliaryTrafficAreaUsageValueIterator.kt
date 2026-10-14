package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AuxiliaryTrafficAreaUsageValueIteratorLib: Library {
    fun ecitygml_AuxiliaryTrafficAreaUsageValueIterator_destroy(handle: Pointer)
    fun ecitygml_AuxiliaryTrafficAreaUsageValueIterator_next(handle: Pointer): Pointer?
}
typealias AuxiliaryTrafficAreaUsageValueIteratorIteratorItem = AuxiliaryTrafficAreaUsageValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class AuxiliaryTrafficAreaUsageValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<AuxiliaryTrafficAreaUsageValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class AuxiliaryTrafficAreaUsageValueIteratorCleaner(val handle: Pointer, val lib: AuxiliaryTrafficAreaUsageValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_AuxiliaryTrafficAreaUsageValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AuxiliaryTrafficAreaUsageValueIterator.AuxiliaryTrafficAreaUsageValueIteratorCleaner(handle, AuxiliaryTrafficAreaUsageValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<AuxiliaryTrafficAreaUsageValueIteratorLib> = AuxiliaryTrafficAreaUsageValueIteratorLib::class.java
        internal val lib: AuxiliaryTrafficAreaUsageValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): AuxiliaryTrafficAreaUsageValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficAreaUsageValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AuxiliaryTrafficAreaUsageValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): AuxiliaryTrafficAreaUsageValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}