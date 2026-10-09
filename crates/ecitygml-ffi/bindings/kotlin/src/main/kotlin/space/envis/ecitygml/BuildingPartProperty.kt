package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface BuildingPartPropertyLib: Library {
    fun ecitygml_BuildingPartProperty_destroy(handle: Pointer)
    fun ecitygml_BuildingPartProperty_object(handle: Pointer): Pointer?
    fun ecitygml_BuildingPartProperty_href(handle: Pointer): Pointer?
}
/** A building part property (inline building part and/or `xlink:href`), borrowed from a city model.
*/
class BuildingPartProperty internal constructor (
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

    private class BuildingPartPropertyCleaner(val handle: Pointer, val lib: BuildingPartPropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_BuildingPartProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, BuildingPartProperty.BuildingPartPropertyCleaner(handle, BuildingPartProperty.lib));
    }

    companion object {
        internal val libClass: Class<BuildingPartPropertyLib> = BuildingPartPropertyLib::class.java
        internal val lib: BuildingPartPropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline building part; none if the property only references one via `href`.
    */
    fun object_(): BuildingPart? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BuildingPartProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = BuildingPart(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BuildingPartProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}