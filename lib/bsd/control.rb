module BSD::Control
  require_relative "control/feature"
  Error = Class.new(RuntimeError)

  ##
  # @return [String]
  #  Returns the version of libhbsdcontrol.
  def self.library_version
    FFI.library_version
  end

  ##
  # @return [Array<BSD::Control::Feature>]
  def self.available_features
    Feature.available
  end

  ##
  # @example
  #   BSD::Control
  #     .feature!(:mprotect)
  #     .enable!("/usr/local/bin/firefox")
  #
  # @param [String] name
  #  The name of a feature.
  #
  # @raise [BSD::Control::Error]
  #  When a feature is not found.
  #
  # @return [BSD::Control::Feature]
  #  Returns an instance of BSD::Control::Feature.
  def self.feature!(name)
    feature = Feature.available.find { _1.name == name.to_s }
    feature ? feature : raise(Error, "feature '#{name}' wasn't found")
  end

  module FFI
  end
end
