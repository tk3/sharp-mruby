using System;

class Example02
{
    static void Main()
    {
//        MRuby.Run("puts \"Welcom to mruby\"");
        TestString();
    }

    static void TestString()
    {
        string src = "ARGV.each do |a| \n"
                   + "  puts \"#{a}, #{a.class}\"\n"
                   + "end";

        MRuby.Run(src, "aa", "bb", "cc");
    }
}
