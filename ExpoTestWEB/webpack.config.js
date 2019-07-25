const HtmlWebPackPlugin = require('html-webpack-plugin')
const CompressionPlugin = require('compression-webpack-plugin')

const htmlPlugin = new HtmlWebPackPlugin({
  template: './src/index.html',
  filename: './index.html'
})

const compressionPlugin = new CompressionPlugin({
  algorithm: 'gzip',
  deleteOriginalAssets: true
})

let config = {
  output: {},
  module: {
    rules: [
      {
        test: /\.(js|jsx)$/,
        exclude: /node_modules/,
        use: ['babel-loader']
      },
      {
        test: /\.scss$/,
        use: ['style-loader', 'css-loader', 'sass-loader']
      },
      {
        test: /\.(png|jpg|gif|svg)$/i,
        use: [
          {
            loader: 'url-loader',
            options: {
              limit: 10000
            }
          }
        ]
      }
    ]
  },
  plugins: [htmlPlugin]
}

module.exports = (env, argv) => {
  if (argv.mode === 'development') {
    config.output.path = __dirname + '/../ExpoTextPIO/data'
  }

  if (argv.mode === 'production') {
    // eslint-disable-next-line
    config.output.path = __dirname + '/../ExpoTextPIO/data'
    config.plugins.push(compressionPlugin)
  }

  return config
}
