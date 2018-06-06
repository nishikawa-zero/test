<?xml version="1.0" encoding="ISO-8859-1"?>
<CarbonProjectFile version="1.0" guid="" type="HDL">
 <EnvironmentVariables/>
 <Preferences>
  <DefaultConfiguration Name="Default"/>
 </Preferences>
 <Sources>
  <Group Name="RTL Model">
   <Configurations>
    <Configuration Name="Default|Linux">
     <Tool Name="RTL Properties">
      <Option Name="-vhdlLib">
       <Value/>
      </Option>
      <Option Name="-vlogLib">
       <Value/>
      </Option>
      <Option Name="Folder Name">
       <Value>RTL Model</Value>
      </Option>
     </Tool>
    </Configuration>
   </Configurations>
   <File RelativePath="../axi_slave.v" LibraryFile="false">
    <FileConfiguration Name="Default">
     <Tool Name="VSPCompilerFile">
      <Option Name="LibraryFile">
       <Value>false</Value>
      </Option>
     </Tool>
    </FileConfiguration>
   </File>
  </Group>
 </Sources>
 <Files/>
 <Platforms>
  <Platform Name="Linux"/>
  <Platform Name="Solaris"/>
 </Platforms>
 <Configurations>
  <Configuration Name="Default|Linux">
   <Tool Name="VSPCompiler">
    <Option Name="-o">
     <Value>libdesign.a</Value>
    </Option>
    <Option Name="-g">
     <Value>true</Value>
    </Option>
    <Option Name="-enableOutputSysTasks">
     <Value>true</Value>
    </Option>
   </Tool>
  </Configuration>
 </Configurations>
 <Tool Name="ProjectOptions">
  <Option Name="Simulation Script Execution">
   <Value>local</Value>
  </Option>
 </Tool>
 <Components>
  <PackageComponent>
   <Configurations>
    <Configuration Name="Default|Linux">
     <Tool Name="VSPCompiler"/>
     <Tool Name="PackageOptions">
      <Option Name="Product Name">
       <Value>Project2</Value>
      </Option>
      <Option Name="Short Name">
       <Value>Project2</Value>
      </Option>
      <Option Name="StandAlone checked">
       <Value>true</Value>
      </Option>
      <Option Name="Version">
       <Value>1</Value>
      </Option>
     </Tool>
    </Configuration>
   </Configurations>
   <PackageContent>
    <PackageFile Name="libProject2.a" Path="./libProject2.a" Component="StandAlone"/>
    <PackageFile Name="libProject2.h" Path="./libProject2.h" Component="StandAlone"/>
   </PackageContent>
  </PackageComponent>
  <MaxsimComponent>
   <Configurations>
    <Configuration Name="Default|Linux">
     <Tool Name="VSPCompiler"/>
     <Tool Name="SOCDesigner">
      <Option Name="Component Name">
       <Value>axi_slave</Value>
      </Option>
     </Tool>
    </Configuration>
   </Configurations>
  </MaxsimComponent>
 </Components>
 <CompilerDirectives>
  <Directives Configuration="Default|Linux">
   <NetDirectives/>
   <ModuleDirectives/>
  </Directives>
 </CompilerDirectives>
 <spirit:component xmlns:spirit="http://www.spiritconsortium.org/XMLSchema/SPIRIT/1.2" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.spiritconsortium.org/XMLSchema/SPIRIT/1.2 http://www.spiritconsortium.org/XMLSchema/SPIRIT/1.2/component.xsd">
  <spirit:vendor/>
  <spirit:library/>
  <spirit:name/>
  <spirit:version/>
  <spirit:memoryMaps/>
 </spirit:component>
</CarbonProjectFile>
