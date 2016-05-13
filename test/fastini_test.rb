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

  def test_load_method_can_parse_multiple_sections
    expected = {'foo' => {'a' => '1'}, 'bar'=> {'b' => '2'}}
    assert_equal expected, Fastini.load("[foo]\na=1\r\n[bar]\nb=2")
  end

  def test_load_method_parse_values_without_a_section
    expected = {'no_section' => '1', 'foo' => {'a' => '1'}}
    assert_equal expected, Fastini.load("no_section=1\n[foo]\na=1")
  end
end
