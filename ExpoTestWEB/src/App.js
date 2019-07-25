import React, { Component } from 'react'
import { ChartLive } from './ChartLive/ChartLive'
import axios from 'axios'

export default class App extends Component {
  constructor (props) {
    super(props)
    this.state = {
      x: 0,
      h: null
    }
    // setInterval(() => this.request(), 1000)
  }

  request () {
      axios.get('http://192.168.4.4/read/humidity', {})
      .then(res => { 
          console.log(res.data.data)
          this.setState({ x: this.state.x + 1, h: res.data.data})
      }).catch(err => {
          console.log(err)
      })
  }
  componentDidMount() {
    setInterval(() => {
      this.request();
    }, 1000);
  }

  render () {
    return (
      <div style={{
        height: "50%",
        transform: "translate(0,50%)"
      }}>
        <center>
          <ChartLive x={this.state.x} y={this.state.h}/>
        </center>
      </div>
    )
  }
}
