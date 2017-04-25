/*
 Copyright (c) 2015, Potion Design LLC
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 * Neither the name of copyright holder nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include "cinder/app/MouseEvent.h"
#include "cinder/app/TouchEvent.h"

#include "poEvents.h"

namespace po { namespace scene {
    
    // Events in poScene extend the functionality of Cinder events
    //
    // First, they include a "Type", which lets you handle multiple events with one
    // function using a switch statement. This is optional, you can of course have a
    // separate function for each event type.
    //
    // Second, they include a source, which lets you
    // subscribe to events from multiple NodeRefs and identify which one is firing using
    // a single method.
    //
    // Last but not least the scene graph allows for Node interaction events,
    // i.e. "Down Inside", "Drag", "Up Inside", etc. which tie into the hit testing functions
    // of all nodes.
    //
    // They also allow for propagation. By default all global events (i.e. "Down", "Move", "Up"
    // propagate to all nodes in the scene. Events like "Down Inside" do not propagate by default,
    // i.e. they will only fire on the top object. You can turn propagation to true on these,
    // and they will continue to fire through the draw tree. You have to set propagation to true
    // everytime an event fires on a node, otherwise the event will stop propagating at that level.
    
    
    class Node;
    typedef std::shared_ptr<Node> NodeRef;
    
    class EventCenter;
	
	
    //------------------------------------
    //	Base Event
    class Event {
        friend class Node;
		
    public:
        Event();
        
        //! Enable/Disable propagation
        void setPropagationEnabled(bool enabled) { mPropagationEnabled = enabled; };
        //! Get propagation enabled
        bool getPropagationEnabled() { return mPropagationEnabled; };
        
        //! Get the position of the event in window Coords
        ci::vec2 getWindowPos() const { return mWindowPos; }
        //! Get the position of the event in coords local to the source node
        ci::vec2 getLocalPos();
        //! Get the position of the event in coords local to the Scene root node
        ci::vec2 getScenePos();
        //! Get the source of the event
        NodeRef getSource() { return mSource.lock(); };
        
    protected:
        void setSource(NodeRef source) { mSource = source; };
        ci::vec2 mWindowPos;
        
    private:
        bool mPropagationEnabled;
        std::weak_ptr<Node> mSource;
    };
	
    
    //------------------------------------
    //	Mouse Event
	//------------------------------------
    
    class MouseEvent
    : public po::scene::Event
    {
        friend class EventCenter;
        
    public:
        //! Mouse event types
        enum Type {
            DOWN,
            DOWN_INSIDE,
            MOVE,
            MOVE_INSIDE,
            DRAG,
            DRAG_INSIDE,
            UP,
            UP_INSIDE,
            WHEEL,
            UNKOWN
        };
        
        MouseEvent(ci::app::MouseEvent event, Type type);
        ci::app::MouseEvent getCiEvent() const { return mCiEvent; };
        Type getType() const { return mType; };
        
    protected:
        void setType(Type type) { mType = type; };
        
    private:
        ci::app::MouseEvent mCiEvent;
        Type mType;
		
    };
    
	
    //------------------------------------
    //	Touch Event
	//------------------------------------
    
    class TouchEvent
    : public Event
    {
        friend class EventCenter;
    public:
        //! Touch Event Types
        enum Type {
            BEGAN,
            BEGAN_INSIDE,
            MOVED,
            MOVED_INSIDE,
            ENDED,
            ENDED_INSIDE,
            UNKOWN
        };
        
        TouchEvent(ci::app::TouchEvent::Touch event, Type type);
        ci::app::TouchEvent::Touch getCiEvent() { return mCiEvent; };
		unsigned int getId() { return mCiEvent.getId(); }
        Type getType() { return mType; }
        
    protected:
        void setType(Type type) { mType = type; };
        
    private:
        ci::app::TouchEvent::Touch mCiEvent;
        Type mType;
		
    };
	
} } //  namespace po::scene