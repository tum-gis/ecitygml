package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface GmlReaderLib: Library {
    fun ecitygml_GmlReader_destroy(handle: Pointer)
    fun ecitygml_GmlReader_new(data: Slice, format: Int): Pointer
    fun ecitygml_GmlReader_from_path(path: Slice): ResultPointerPointer
    fun ecitygml_GmlReader_with_rebuild_object_bounds(handle: Pointer, rebuildObjectBounds: Boolean): Unit
    fun ecitygml_GmlReader_finish(handle: Pointer): ResultPointerPointer
}
/** Reads CityGML from a file or from memory. Rust's builder methods take the reader by value,
*which Diplomat can't express: here they modify it in place, and `finish` can be called only once.
*/
class GmlReader internal constructor (
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

    private class GmlReaderCleaner(val handle: Pointer, val lib: GmlReaderLib) : Runnable {
        override fun run() {
            lib.ecitygml_GmlReader_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, GmlReader.GmlReaderCleaner(handle, GmlReader.lib));
    }

    companion object {
        internal val libClass: Class<GmlReaderLib> = GmlReaderLib::class.java
        internal val lib: GmlReaderLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** Reads CityGML content of the given `format` from memory, e.g. in WebAssembly, where there is
        *no file system. The data is copied.
        */
        fun create(data: UByteArray, format: CitygmlFormat): GmlReader {
            val dataSliceMemory = PrimitiveArrayTools.borrow(data)
            
            val returnVal = lib.ecitygml_GmlReader_new(dataSliceMemory.slice, format.toNative());
            try {
                val selfEdges: List<Any> = listOf()
                val handle = returnVal 
                val returnOpaque = GmlReader(handle, selfEdges, true)
                return returnOpaque
            } finally {
                dataSliceMemory.close()
            }
        }
        @JvmStatic
        
        /** Opens the CityGML file at `path` (`.gml`, `.gml.gz` or `.gml.zst`).
        */
        fun fromPath(path: String): Result<GmlReader> {
            val pathSliceMemory = PrimitiveArrayTools.borrowUtf8(path)
            
            val returnVal = lib.ecitygml_GmlReader_from_path(pathSliceMemory.slice);
            try {
                val nativeOkVal = returnVal.getNativeOk();
                if (nativeOkVal != null) {
                    val selfEdges: List<Any> = listOf()
                    val handle = nativeOkVal 
                    val returnOpaque = GmlReader(handle, selfEdges, true)
                    return returnOpaque.ok()
                } else {
                    val selfEdges: List<Any> = listOf()
                    val handle = returnVal.getNativeErr()!! 
                    val returnOpaque = Error(handle, selfEdges, true)
                    return returnOpaque.err()
                }
            } finally {
                pathSliceMemory.close()
            }
        }
    }
    
    /** Whether envelopes of child objects are recomputed from their geometry (default: true).
    *Has no effect after `finish`.
    */
    fun withRebuildObjectBounds(rebuildObjectBounds: Boolean): Unit {
        
        val returnVal = lib.ecitygml_GmlReader_with_rebuild_object_bounds(handle, rebuildObjectBounds);
        
    }
    
    /** Reads the city model; fails with `InvalidArgument` if called a second time.
    */
    fun finish(): Result<CityModel> {
        
        val returnVal = lib.ecitygml_GmlReader_finish(handle);
        val nativeOkVal = returnVal.getNativeOk();
        if (nativeOkVal != null) {
            val selfEdges: List<Any> = listOf()
            val handle = nativeOkVal 
            val returnOpaque = CityModel(handle, selfEdges, true)
            return returnOpaque.ok()
        } else {
            val selfEdges: List<Any> = listOf()
            val handle = returnVal.getNativeErr()!! 
            val returnOpaque = Error(handle, selfEdges, true)
            return returnOpaque.err()
        }
    }

}