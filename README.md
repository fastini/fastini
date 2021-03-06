# fastini

C extension that parses INI configuration and data files.

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'fastini'
```
And then execute:

    $ bundle

Or install it yourself as:

    $ gem install fastini

## Usage

For now only four methods are implemented with a limited set of INI
configuration.

```ruby
Fastini.load("[foo]\na=1\n[bar]\nb=2")
{'foo' => {'a' => '1'}, 'bar'=> {'b' => '2'}}

Fastini.load_file('my_file.ini')
{'foo' => {'a' => '1'}, 'bar'=> {'b' => '2'}}

Fastini.dump({foo: 1, bar: {c: 2}})
"foo=1\n\n[bar]\nc=2\n"

Fastini.dump_file({foo: 1, bar: {c: 2}}, 'my_file.out')
$ cat my_file.out
"foo=1\n\n[bar]\nc=2\n"
```

### What is accepted for now?

- Comments with `#` or `;` (but not inline comments)
- Sections
- Simple assignments

### What is planned for next releases?

- Multiline assignments (value in multiple lines with the `\` separator)
- Repeated keys generating an array of values

## Development

After checking out the repo, run `bin/setup` to install dependencies. Then, run `rake test` to run the tests. You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version, push git commits and tags, and push the `.gem` file to [rubygems.org](https://rubygems.org).

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/[USERNAME]/fastini. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [Contributor Covenant](http://contributor-covenant.org) code of conduct.

## License

The gem is available as open source under the terms of the [MIT License](./LICENSE).

