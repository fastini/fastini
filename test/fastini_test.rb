require 'test_helper'
require 'fastini'

class FastiniTest < Minitest::Test
  def test_that_it_has_a_version_number
    refute_nil ::Fastini::VERSION
  end

  def test_load_method_expects_a_string
    assert_raises TypeError do
      Fastini.load(nil)
    end
  end

  def test_load_method_raises_with_malformed_section
    e = assert_raises SyntaxError do
      Fastini.load("[foo\na=1")
    end

    error_message = 'section must have an end'
    assert_equal error_message, e.message
  end

  def test_load_method_raises_with_malformed_assignment
    e = assert_raises SyntaxError do
      Fastini.load("[foo]\ninvalid:1\n")
    end

    error_message = "values must be assigned with the '=' symbol"
    assert_equal error_message, e.message
  end

  def test_load_method_returns_hash_with_valid_string
    expected = {}
    assert_equal expected, Fastini.load('')
  end

  def test_load_method_can_parse_sections
    expected = {'foo' => {'a' => '1'}, 'bar'=> {'b' => '2'}}
    assert_equal expected, Fastini.load("[foo]\na=1\r\n[bar]\nb=2")
  end

  def test_load_method_ignores_comments
    expected = {'foo' => {'a' => '1'}}
    assert_equal expected, Fastini.load(";cool comment\n[foo]\na=1")
  end

  def test_load_method_parse_values_without_a_section
    expected = {'no_section' => '1', 'foo' => {'a' => '1'}}
    assert_equal expected, Fastini.load("no_section=1\n[foo]\na=1")
  end

  def test_load_file_method_with_valid_path
    expected = {'no_section' => '1', 'foo' => {'a' => '2'}, 'bar'=>{'b' => '3'}}
    assert_equal expected, Fastini.load_file('./test/load_file.in')
  end

  def test_load_file_method_with_invalid_path
    e = assert_raises StandardError do
      Fastini.load_file('no_file')
    end

    error_message = 'file not found'
    assert_equal error_message, e.message
  end

  def test_dump_method_expects_a_hash
    e = assert_raises TypeError do
      Fastini.dump(nil)
    end

    error_message = 'argument must be a Hash'
    assert_equal error_message, e.message
  end

  def test_dump_method_returns_an_utf8_string_with_ini_format
    assert_equal "a=1\n\n[b]\nc=2\n", Fastini.dump({a: 1, b: {c: 2}})
    assert_equal 'UTF-8', Fastini.dump({a: 1, b: {c: 2}}).encoding.to_s
  end

  def test_dump_file_method_expects_a_hash
    e = assert_raises TypeError do
      Fastini.dump_file(nil, 'my_file_path')
    end

    error_message = 'argument must be a Hash'
    assert_equal error_message, e.message
  end

  def test_dump_file_method_with_invalid_path
    e = assert_raises StandardError do
      Fastini.dump_file({a: 1}, './invalid_path/dump_file.out')
    end

    error_message = 'invalid file path'
    assert_equal error_message, e.message
  end

  def test_dump_file_method_generates_a_file_with_ini_format
    file_path = './test/dump_file.out'
    Fastini.dump_file({a: 1, b: {c: 2}}, file_path)
    assert_equal "a=1\n\n[b]\nc=2\n", File.read(file_path)
    File.delete(file_path)
  end
end
