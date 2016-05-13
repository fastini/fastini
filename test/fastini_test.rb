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
    assert_raises SyntaxError do
      Fastini.load("[foo\na=1\nb=2")
    end
  end

  def test_load_method_returns_hash_with_valid_string
    expected = { 'foo' => {} }
    assert_equal expected, Fastini.load("[foo] \n  a=1\r\n  b=2")
  end
end
