using System;

class Example02
{
    static  string src = @"
        ARGV.each do |a|
          puts ""#{a}, #{a.class}""
        end";

    static void Main()
    {
        TestString();
        TestBoolean();
        TestInt32();
    }

    static void TestString()
    {

        MRuby.Run(src, "00", "aa", "bb", "cc");
    }

    static void TestBoolean()
    {
        MRuby.Run(src, "01", true, false);
    }

    static void TestInt32()
    {
        MRuby.Run(src, "02", 11, 23, 35);
    }
}
