package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface CityObjectRelationPropertyLib: Library {
    fun ecitygml_CityObjectRelationProperty_destroy(handle: Pointer)
    fun ecitygml_CityObjectRelationProperty_object(handle: Pointer): Pointer?
    fun ecitygml_CityObjectRelationProperty_href(handle: Pointer): Pointer?
}
/** A city object relation property (inline relation and/or `xlink:href`), borrowed from a
*city model.
*/
class CityObjectRelationProperty internal constructor (
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

    private class CityObjectRelationPropertyCleaner(val handle: Pointer, val lib: CityObjectRelationPropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_CityObjectRelationProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, CityObjectRelationProperty.CityObjectRelationPropertyCleaner(handle, CityObjectRelationProperty.lib));
    }

    companion object {
        internal val libClass: Class<CityObjectRelationPropertyLib> = CityObjectRelationPropertyLib::class.java
        internal val lib: CityObjectRelationPropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline relation; none if the property only references one via `href`.
    */
    fun object_(): CityObjectRelation? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityObjectRelationProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = CityObjectRelation(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityObjectRelationProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}