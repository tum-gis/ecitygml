package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface BuildingPartPropertyIteratorLib: Library {
    fun ecitygml_BuildingPartPropertyIterator_destroy(handle: Pointer)
    fun ecitygml_BuildingPartPropertyIterator_next(handle: Pointer): Pointer?
}
typealias BuildingPartPropertyIteratorIteratorItem = BuildingPartProperty?
/** Iterates over building part properties, borrowed from a city model.
*/
class BuildingPartPropertyIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<BuildingPartProperty?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class BuildingPartPropertyIteratorCleaner(val handle: Pointer, val lib: BuildingPartPropertyIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_BuildingPartPropertyIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, BuildingPartPropertyIterator.BuildingPartPropertyIteratorCleaner(handle, BuildingPartPropertyIterator.lib));
    }

    companion object {
        internal val libClass: Class<BuildingPartPropertyIteratorLib> = BuildingPartPropertyIteratorLib::class.java
        internal val lib: BuildingPartPropertyIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): BuildingPartProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BuildingPartPropertyIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = BuildingPartProperty(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): BuildingPartProperty?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}