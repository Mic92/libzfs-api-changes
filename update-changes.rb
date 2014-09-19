#!/usr/bin/env ruby
require 'fileutils'
require 'set'
require 'rake/file_list'

def sh(cmd, *args)
  pretty_args = args.map {|arg| "'#{arg}'"}
  puts (["$ ", cmd] + pretty_args).join(" ")

  stdout = IO.popen([cmd] + args)
  res = stdout.read
  puts res
  abort "Command exited abnormally" unless $?.to_i == 0
  res
end

def release_tags
  out = sh("git", "tag")
  tags = out.split
  tags.keep_if {|tag| tag =~/zfs-/ }
end

unless Dir.exist?("zfsonlinux")
  sh "git", "clone", "https://github.com/zfsonlinux/zfs.git", "zfsonlinux"
end

commited_releases = Set.new(release_tags)

Dir.chdir("zfsonlinux") do
  sh "git", "fetch"
  available_releases = Set.new(release_tags)
  todo = available_releases - commited_releases
  todo.each do |release|
    sh "git", "checkout", release
    FileUtils.rm_rf "../include"
    FileUtils.mkdir "../include"
    includes = Rake::FileList.new("**/include/**/*.h")
    includes.each do |inc|
      dest = inc[/include\/.+/]
      puts "cp '#{inc}' '../#{dest}'"
      FileUtils.mkdir_p "../#{File.dirname(dest)}"
      FileUtils.cp_r inc, "../#{dest}"
    end
    Dir.chdir("..") do
      sh "git", "add", "include"
      sh "git", "commit", "-m", release
      sh "git", "tag", release
    end
  end
end
