# frozen_string_literal: true

require 'charma'
require "json"
require "pp"

data = JSON.parse( File.open( "result.json", &:read ) )

Charma::Document.new do |doc|
  opts = data.map{ |name,v|
    {
      title:name,
      bins:100,
      series:[
        {
          y:v.map{ |_,v| v }
        }
      ],
      x_ticks:v.map{ |k,_| k }

    }
  }
  opts.each do |o|
    doc.new_page do |page|
      page.add_violinchart( o )
    end
  end
  doc.render( File.basename(__FILE__, ".*")+".pdf" )
end
