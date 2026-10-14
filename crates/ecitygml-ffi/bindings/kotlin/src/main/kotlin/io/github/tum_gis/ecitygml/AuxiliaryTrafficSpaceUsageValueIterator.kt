package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AuxiliaryTrafficSpaceUsageValueIteratorLib: Library {
    fun ecitygml_AuxiliaryTrafficSpaceUsageValueIterator_destroy(handle: Pointer)
    fun ecitygml_AuxiliaryTrafficSpaceUsageValueIterator_next(handle: Pointer): Pointer?
}
typealias AuxiliaryTrafficSpaceUsageValueIteratorIteratorItem = AuxiliaryTrafficSpaceUsageValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class AuxiliaryTrafficSpaceUsageValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<AuxiliaryTrafficSpaceUsageValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class AuxiliaryTrafficSpaceUsageValueIteratorCleaner(val handle: Pointer, val lib: AuxiliaryTrafficSpaceUsageValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_AuxiliaryTrafficSpaceUsageValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AuxiliaryTrafficSpaceUsageValueIterator.AuxiliaryTrafficSpaceUsageValueIteratorCleaner(handle, AuxiliaryTrafficSpaceUsageValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<AuxiliaryTrafficSpaceUsageValueIteratorLib> = AuxiliaryTrafficSpaceUsageValueIteratorLib::class.java
        internal val lib: AuxiliaryTrafficSpaceUsageValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): AuxiliaryTrafficSpaceUsageValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficSpaceUsageValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AuxiliaryTrafficSpaceUsageValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): AuxiliaryTrafficSpaceUsageValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}