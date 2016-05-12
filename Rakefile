require 'bundler/gem_tasks'
require 'rake/extensiontask'
require 'rake/testtask'

gem = Gem::Specification.load(File.dirname(__FILE__) + '/fastini.gemspec')
Rake::ExtensionTask.new('fastini', gem) do |ext|
  ext.lib_dir = 'lib/fastini'
end

Rake::TestTask.new(:test) do |t|
  t.libs << 'test'
  t.libs << 'lib'
  t.test_files = FileList['test/**/*_test.rb']
end

task :default => [:compile, :test]
