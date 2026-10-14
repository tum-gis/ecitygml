package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AuxiliaryTrafficSpacePropertyIteratorLib: Library {
    fun ecitygml_AuxiliaryTrafficSpacePropertyIterator_destroy(handle: Pointer)
    fun ecitygml_AuxiliaryTrafficSpacePropertyIterator_next(handle: Pointer): Pointer?
}
typealias AuxiliaryTrafficSpacePropertyIteratorIteratorItem = AuxiliaryTrafficSpaceProperty?
/** Iterates over auxiliary traffic space properties, borrowed from a city model.
*/
class AuxiliaryTrafficSpacePropertyIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<AuxiliaryTrafficSpaceProperty?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class AuxiliaryTrafficSpacePropertyIteratorCleaner(val handle: Pointer, val lib: AuxiliaryTrafficSpacePropertyIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_AuxiliaryTrafficSpacePropertyIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AuxiliaryTrafficSpacePropertyIterator.AuxiliaryTrafficSpacePropertyIteratorCleaner(handle, AuxiliaryTrafficSpacePropertyIterator.lib));
    }

    companion object {
        internal val libClass: Class<AuxiliaryTrafficSpacePropertyIteratorLib> = AuxiliaryTrafficSpacePropertyIteratorLib::class.java
        internal val lib: AuxiliaryTrafficSpacePropertyIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): AuxiliaryTrafficSpaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficSpacePropertyIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AuxiliaryTrafficSpaceProperty(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): AuxiliaryTrafficSpaceProperty?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}