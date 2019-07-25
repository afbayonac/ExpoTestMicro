import React, { Component } from 'react'
import { select, scaleLinear, axisBottom, axisLeft, max, line, min} from "d3";
import './style.scss'

export class ChartLive extends Component{
    constructor(props){
        super(props)
        this.state= {
            data: [
            ]
        }
        this.nodeRef = null;
        this.margin = {top: 10, right: 30, bottom: 30, left: 50},
        this.width = 460 - this.margin.left - this.margin.right,
        this.height = 400 - this.margin.top - this.margin.bottom;
         
    }
    setRef(ref) {
          this.nodeRef = ref;
    }

    UpdateChart () {
        // Create the X axis:
        this.x.domain([min(this.state.data, function(d) { return d.x }), max(this.state.data, function(d) { return d.x }) ]);
        this.svg.selectAll(".myXaxis").transition()
            .duration(20)
            .call(this.xAxis);
        
        // create the Y axis
        this.y.domain([0, 100 ]);
        this.svg.selectAll(".myYaxis")
            .transition()
            .duration(20)
            .call(this.yAxis);
        
        // Create a update selection: bind to the new data
        this.u = this.svg.selectAll(".lineTest")
            .data([this.state.data], function(d){ return d.x });
        
        let x = this.x
        let y = this.y
        // Updata the line
        this.u
            .enter()
            .append("path")
            .attr("class","lineTest")
            .merge(this.u)
            .transition()
            .duration(500)
            .attr("d", line()
            .x(function(d) { return x(d.x); })
            .y(function(d) { return y(d.y); }))
            .attr("fill", "none")
            .attr("stroke", "steelblue")
            .attr("stroke-width", 2.5)
    }
    
    componentWillReceiveProps (props) {
        console.log(props)
        let {x, y} = props
        let data = this.state.data
        if(data.length > 30) data.shift()
        this.setState({data: [...data, {x: x , y : y}]})
        this.UpdateChart()
    }
    componentDidMount() {


        let {margin, width, height} = this
        console.log(this)
        this.svg = select(this.nodeRef)
        .append("svg")
            .attr("width", width + margin.left + margin.right)
            .attr("height", height + margin.top + margin.bottom)
        .append("g")
            .attr("transform",
                "translate(" + margin.left + "," + margin.top + ")");
        
        this.x = scaleLinear().range([0,width]);
        this.xAxis = axisBottom().scale(this.x);
        this.svg.append("g")
            .attr("transform", "translate(0," + height + ")")
            .attr("class","myXaxis")

        // Initialize an Y axis
        this.y = scaleLinear().range([height, 0]);
        this.yAxis = axisLeft().scale(this.y);
        this.svg.append("g")
            .attr("class","myYaxis")
                
    }
      
    request (pin, status) {
        this.setState({ classState: '' })
        axios.post('http://192.168.4.4/readHumedity', {
            status, pin
        }).then(res => { 
            this.setState({ classState: 'botton-ok' })
        }).catch(error => {
            this.setState({
                classState: 'botton-err'
            })
        })
    }

    shouldComponentUpdate() {
        // Suspendemos los renders de React.
        return false;
    }

    render () {  
        return (
            <div  className="container" ref={(ref) => this.setRef(ref)} />)
    }
}