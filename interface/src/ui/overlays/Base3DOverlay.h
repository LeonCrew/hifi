//
//  Base3DOverlay.h
//  interface/src/ui/overlays
//
//  Copyright 2014 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_Base3DOverlay_h
#define hifi_Base3DOverlay_h

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <BoxBase.h>
#include <Transform.h>

#include "Overlay.h"

class Base3DOverlay : public Overlay {
    Q_OBJECT
    
public:
    Base3DOverlay();
    Base3DOverlay(const Base3DOverlay* base3DOverlay);

    // getters
    virtual bool is3D() const { return true; }
    const glm::vec3& getPosition() const { return _transform.getTranslation(); }
    const glm::quat& getRotation() const { return _transform.getRotation(); }
   
    // TODO: consider implementing registration points in this class
    const glm::vec3& getCenter() const { return getPosition(); }
    
    float getLineWidth() const { return _lineWidth; }
    bool getIsSolid() const { return _isSolid; }
    bool getIsDashedLine() const { return _isDashedLine; }
    bool getIsSolidLine() const { return !_isDashedLine; }
    bool getIgnoreRayIntersection() const { return _ignoreRayIntersection; }
    bool getDrawInFront() const { return _drawInFront; }
    bool getDrawOnHUD() const { return _drawOnHUD; }

    // setters
    void setPosition(const glm::vec3& value) { _transform.setTranslation(value); }
    void setRotation(const glm::quat& value) { _transform.setRotation(value); }
    
    void setLineWidth(float lineWidth) { _lineWidth = lineWidth; }
    void setIsSolid(bool isSolid) { _isSolid = isSolid; }
    void setIsDashedLine(bool isDashedLine) { _isDashedLine = isDashedLine; }
    void setIgnoreRayIntersection(bool value) { _ignoreRayIntersection = value; }
    void setDrawInFront(bool value) { _drawInFront = value; }
    void setDrawOnHUD(bool value) { _drawOnHUD = value; }

    virtual AABox getBounds() const = 0;

    virtual void setProperties(const QScriptValue& properties);
    virtual QScriptValue getProperty(const QString& property);

    virtual bool findRayIntersection(const glm::vec3& origin, const glm::vec3& direction, float& distance, BoxFace& face);

    virtual bool findRayIntersectionExtraInfo(const glm::vec3& origin, const glm::vec3& direction, 
                                                    float& distance, BoxFace& face, QString& extraInfo) {
            return findRayIntersection(origin, direction, distance, face);
    }

protected:
    Transform _transform;
    
    float _lineWidth;
    bool _isSolid;
    bool _isDashedLine;
    bool _ignoreRayIntersection;
    bool _drawInFront;
    bool _drawOnHUD;
};
 
#endif // hifi_Base3DOverlay_h
