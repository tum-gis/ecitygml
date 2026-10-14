package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface ImplicitGeometryLib: Library {
    fun ecitygml_ImplicitGeometry_destroy(handle: Pointer)
    fun ecitygml_ImplicitGeometry_object_id(handle: Pointer): Pointer
    fun ecitygml_ImplicitGeometry_transformation_matrix(handle: Pointer): Pointer
    fun ecitygml_ImplicitGeometry_mime_type(handle: Pointer): Pointer?
    fun ecitygml_ImplicitGeometry_library_object(handle: Pointer): OptionSlice
    fun ecitygml_ImplicitGeometry_reference_point(handle: Pointer): Pointer
    fun ecitygml_ImplicitGeometry_relative_geometry(handle: Pointer): Pointer?
    fun ecitygml_ImplicitGeometry_compute_envelope(handle: Pointer): Pointer?
}
/** A prototype geometry placed by a transformation and a reference point, borrowed from a city
*model. Not bound yet: appearances.
*/
class ImplicitGeometry internal constructor (
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

    private class ImplicitGeometryCleaner(val handle: Pointer, val lib: ImplicitGeometryLib) : Runnable {
        override fun run() {
            lib.ecitygml_ImplicitGeometry_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, ImplicitGeometry.ImplicitGeometryCleaner(handle, ImplicitGeometry.lib));
    }

    companion object {
        internal val libClass: Class<ImplicitGeometryLib> = ImplicitGeometryLib::class.java
        internal val lib: ImplicitGeometryLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** Identifies the implicit geometry (from its `gml:id`).
    */
    fun objectId(): Id {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ImplicitGeometry_object_id(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Id(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun transformationMatrix(): TransformationMatrix4x4 {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ImplicitGeometry_transformation_matrix(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = TransformationMatrix4x4(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun mimeType(): MimeTypeValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ImplicitGeometry_mime_type(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MimeTypeValue(handle, selfEdges, false)
        return returnOpaque
    }
    
    /** Reference to the prototype in an external library.
    */
    fun libraryObject(): String? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ImplicitGeometry_library_object(handle);
        
        val intermediateOption = returnVal.option() ?: return null
            return PrimitiveArrayTools.getUtf8(intermediateOption)
                                
    }
    
    fun referencePoint(): PointProperty {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ImplicitGeometry_reference_point(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = PointProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    /** The prototype geometry, in its own coordinate system.
    */
    fun relativeGeometry(): AbstractGeometryProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ImplicitGeometry_relative_geometry(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractGeometryProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    /** Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
    */
    fun computeEnvelope(): Envelope? {
        
        val returnVal = lib.ecitygml_ImplicitGeometry_compute_envelope(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, true)
        return returnOpaque
    }

}