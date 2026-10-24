package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TrafficSpaceReferenceLib: Library {
    fun ecitygml_TrafficSpaceReference_destroy(handle: Pointer)
}
/** A reference to a traffic space by `xlink:href`, borrowed from a city model. Like in Rust, it
*has no accessors of its own: convert it with `Reference::from_traffic_space_reference`.
*/
class TrafficSpaceReference internal constructor (
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

    private class TrafficSpaceReferenceCleaner(val handle: Pointer, val lib: TrafficSpaceReferenceLib) : Runnable {
        override fun run() {
            lib.ecitygml_TrafficSpaceReference_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TrafficSpaceReference.TrafficSpaceReferenceCleaner(handle, TrafficSpaceReference.lib));
    }

    companion object {
        internal val libClass: Class<TrafficSpaceReferenceLib> = TrafficSpaceReferenceLib::class.java
        internal val lib: TrafficSpaceReferenceLib = Native.load("ecitygml_ffi", libClass)
    }

}