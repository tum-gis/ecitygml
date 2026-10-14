package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface DateLib: Library {
    fun ecitygml_Date_destroy(handle: Pointer)
    fun ecitygml_Date_from_parts(year: Int, month: FFIUint32, day: FFIUint32, offsetSeconds: Int): ResultPointerPointer
    fun ecitygml_Date_year(handle: Pointer): Int
    fun ecitygml_Date_month(handle: Pointer): FFIUint32
    fun ecitygml_Date_day(handle: Pointer): FFIUint32
    fun ecitygml_Date_offset_seconds(handle: Pointer): Int
    fun ecitygml_Date_start_of_day(handle: Pointer): Pointer
}
/** A calendar date with a timezone, created or borrowed from a city model.
*/
class Date internal constructor (
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

    private class DateCleaner(val handle: Pointer, val lib: DateLib) : Runnable {
        override fun run() {
            lib.ecitygml_Date_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Date.DateCleaner(handle, Date.lib));
    }

    companion object {
        internal val libClass: Class<DateLib> = DateLib::class.java
        internal val lib: DateLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** Creates a date from its fields and the offset east of UTC in seconds; fails with
        *`InvalidArgument` for invalid fields or offsets.
        */
        fun fromParts(year: Int, month: UInt, day: UInt, offsetSeconds: Int): Result<Date> {
            
            val returnVal = lib.ecitygml_Date_from_parts(year, FFIUint32(month), FFIUint32(day), offsetSeconds);
            val nativeOkVal = returnVal.getNativeOk();
            if (nativeOkVal != null) {
                val selfEdges: List<Any> = listOf()
                val handle = nativeOkVal 
                val returnOpaque = Date(handle, selfEdges, true)
                return returnOpaque.ok()
            } else {
                val selfEdges: List<Any> = listOf()
                val handle = returnVal.getNativeErr()!! 
                val returnOpaque = Error(handle, selfEdges, true)
                return returnOpaque.err()
            }
        }
    }
    
    fun year(): Int {
        
        val returnVal = lib.ecitygml_Date_year(handle);
        return (returnVal)
    }
    
    /** 1 to 12.
    */
    fun month(): UInt {
        
        val returnVal = lib.ecitygml_Date_month(handle);
        return (returnVal.toUInt())
    }
    
    /** 1 to 31.
    */
    fun day(): UInt {
        
        val returnVal = lib.ecitygml_Date_day(handle);
        return (returnVal.toUInt())
    }
    
    /** The UTC offset in seconds (local time minus UTC).
    */
    fun offsetSeconds(): Int {
        
        val returnVal = lib.ecitygml_Date_offset_seconds(handle);
        return (returnVal)
    }
    
    /** Midnight at the start of the date, in the date's timezone.
    */
    fun startOfDay(): DateTime {
        
        val returnVal = lib.ecitygml_Date_start_of_day(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = DateTime(handle, selfEdges, true)
        return returnOpaque
    }

}