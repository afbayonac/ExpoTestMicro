import React from 'react'
import ReactDOM from 'react-dom'
import { BrowserRouter, Route } from 'react-router-dom'
import App from './App'
import './style.scss'

const root = (
  <BrowserRouter>
    <Route path='/' component={App}/>
  </BrowserRouter>
)

ReactDOM.render(root, document.getElementById('index'))
