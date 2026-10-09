package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface BoundingShapeLib: Library {
    fun ecitygml_BoundingShape_destroy(handle: Pointer)
    fun ecitygml_BoundingShape_envelope(handle: Pointer): Pointer?
}
/** The bounding shape of a feature (`gml:boundedBy`), borrowed from a city model.
*/
class BoundingShape internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal var owned: Boolean,
)  {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class BoundingShapeCleaner(val handle: Pointer, val lib: BoundingShapeLib) : Runnable {
        override fun run() {
            lib.ecitygml_BoundingShape_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, BoundingShape.BoundingShapeCleaner(handle, BoundingShape.lib));
    }

    companion object {
        internal val libClass: Class<BoundingShapeLib> = BoundingShapeLib::class.java
        internal val lib: BoundingShapeLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The envelope; none if the shape is nil.
    */
    fun envelope(): Envelope? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BoundingShape_envelope(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, false)
        return returnOpaque
    }

}