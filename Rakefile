
INCLUDES = %q{/I.\include /I.\vender\mruby\include}
NET_FRAMEWORK = %q{C:\Windows\Microsoft.NET\Framework\v4.0.30319}
NET_ASM_4 = %q{C:\Program Files\Reference Assemblies\Microsoft\Framework\.NETFramework\v4.0}

VS2012_BIN = %q{C:\Program Files\Microsoft Visual Studio 11.0\VC\bin}
VS2012_IDE = %q{C:\Program Files\Microsoft Visual Studio 11.0\Common7\IDE}

VS2012_INCLUDE = %q{C:\Program Files\Microsoft Visual Studio 11.0\VC\INCLUDE;C:\Program Files\Windows Kits\8.0\include\shared;C:\Program Files\Windows Kits\8.0\include\um;C:\Program Files\Windows Kits\8.0\include\winrt;}
VS2012_LIB = %q{C:\Program Files\Microsoft Visual Studio 11.0\VC\LIB;C:\Program Files\Windows Kits\8.0\lib\win8\um\x86;}
VS2012_LIBPATH=%q{C:\Windows\Microsoft.NET\Framework\v4.0.30319;C:\Windows\Microsoft.NET\Framework\v3.5;C:\Program Files\Microsoft Visual Studio 11.0\VC\LIB;C:\Program Files\Windows Kits\8.0\References\CommonConfiguration\Neutral;C:\Program Files\Microsoft SDKs\Windows\v8.0\ExtensionSDKs\Microsoft.VCLibs\11.0\References\CommonConfiguration\neutral;}

MRUBY_LIB = %q{.\vender\mruby\build\host\lib\libmruby.lib}

DEF_LIBS = %q{kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib}

ENV['PATH'] += ";#{VS2012_BIN}"
ENV['PATH'] += ";#{VS2012_IDE}"
ENV['PATH'] += ";#{NET_FRAMEWORK}"
ENV['INCLUDE'] = VS2012_INCLUDE
ENV['LIB']     = VS2012_LIB
ENV['LIBPATH'] = VS2012_LIBPATH

#CLI_CFLAGS = %Q{/AI"#{NET_ASM_4}" /Zi /clr /nologo /W3 /WX- /Od /Oy- /D WIN32 /D _DEBUG /D _WINDLL /D _UNICODE /D UNICODE /EHa /MDd /GS /fp:precise /Zc:wchar_t /Zc:forScope /TP /analyze- /errorReport:prompt /clr:nostdlib}
#CLI_LFLAGS = %Q{/ERRORREPORT:PROMPT /INCREMENTAL /NOLOGO #{MRUBY_LIB} #{DEF_LIBS} /MANIFEST /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /DEBUG /ASSEMBLYDEBUG /TLBID:1 /DYNAMICBASE /FIXED:NO /NXCOMPAT /MACHINE:X86 /DLL}
CLI_CFLAGS = %Q{/AI"#{NET_ASM_4}" /Zi /clr /nologo /W3 /WX- /Od /Oy- /D WIN32 /D _WINDLL /D _UNICODE /D UNICODE /EHa /MDd /GS /fp:precise /Zc:wchar_t /Zc:forScope /TP /analyze- /errorReport:prompt /clr:nostdlib}
CLI_LFLAGS = %Q{/ERRORREPORT:PROMPT /INCREMENTAL /NOLOGO #{MRUBY_LIB} #{DEF_LIBS} /MANIFEST /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /TLBID:1 /DYNAMICBASE /FIXED:NO /NXCOMPAT /MACHINE:X86 /DLL}

########

require 'rake/clean'


CLI_NAME = "sharp-mruby"
CLI_OUT  = "build/sharpmruby/"
CLI_SRCS = FileList["src/*.cpp"]
CLI_OBJS = CLI_SRCS.map{|f| CLI_OUT + File.basename(f).ext('obj')}

CLOBBER.include(CLI_OUT)

task :default => [:init, "sharp-mruby"]

task :init do
  mkdir_p(CLI_OUT)
end

file "sharp-mruby" => [CLI_OBJS] do |task|
  objs = task.prerequisites.map{|f| CLI_OUT + File.basename(f)}.join(' ')

  sh %Q{link #{CLI_LFLAGS} /OUT:#{CLI_OUT}#{task.name}.dll } +
      %Q{/ManifestFile:#{CLI_OUT}#{task.name}.dll.intermediate.manifest } +
      %Q{/PDB:#{CLI_OUT}foo.pdb #{objs}}
end

rule '.obj' => [ proc {|n| "src/" + File.basename(n).ext('cpp')} ] do |t|
  sh %Q{cl /c #{INCLUDES} #{CLI_CFLAGS} } +
     %Q{/Fo#{CLI_OUT} /Fd#{CLI_OUT}vc100.pdb #{t.source}}
end

require "pp"

namespace :example do
  task :init do
    copy "#{CLI_OUT}#{CLI_NAME}.dll", "./example"
  end

  task "01" => :init do |t|
    cd "example" do
      sh %Q{csc /nologo /t:exe /out:example01.exe /reference:#{CLI_NAME}.dll example01.cs}
    end
  end
end

