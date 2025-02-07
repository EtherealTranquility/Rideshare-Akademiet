# Rideshare-Akademiet

## Prosjektbeskrivelse

Rideshare-Akademiet-prosjektet har som mål å samle og analysere data fra en rakett ved hjelp av en Arduino-enhet. Dataene skal enten lagres på et SD-kort eller sendes via rakettens antenne til bakken, hvor de vil bli analysert og visualisert med Python. Det er fortsatt usikkerhet rundt hvordan payloaden skal implementeres, men målet er å få oversikt over rakettens oppførsel under oppskyting og nedstigning.

## Hva må gjøres / Problemstillinger

1. **Arduino-programmering**
   - Sensorer: Skriv Arduino-kode som samler data fra ulike sensorer under rakettens oppskyting.
   - Dataoverføring: Implementer funksjonalitet for å lagre dataene på et SD-kort eller sende dem til bakken via rakettens antenne.

2. **Lagring av data**
   - Alternativ 1: Lagring på SD-kort
     - Definer hvordan dataene skal lagres (f.eks. CSV eller JSON-format).
   - Alternativ 2: Sanntidsoverføring via antenne
     - Bruk rakettens antenne for å sende dataene til bakken under oppskytingen, og ta imot disse dataene med en mottaker.

3. **Format på lagrede data**
   - Velg et passende format for lagring og videre analyse:
     - CSV: Lett å eksportere til regneark og bruke i databehandlingsverktøy.
     - JSON: Lett tilgjengelig og strukturert, ideelt for bruk med Python for videre analyse.

4. **Oppstart av kortet**
   - Lag en mekanisme for å starte SD-kortet, for eksempel:
     - Automatisk oppstart ved tilkobling til strøm.
     - En timer-trigger for oppstart etter en viss tid.

5. **Python-datavisualisering**
   - Lag et Python-program for å importere og visualisere de lagrede dataene fra SD-kortet eller antennemottakeren.
   - Visualiser dataene med grafer for å analysere rakettens oppførsel under oppskyting og nedstigning.

6. **Sanntidsvisualisering**
   - Alternativ til lagring og etteranalyse: Visualiser dataene i sanntid mens raketten er i luften.
   - Bruk dataene som sendes via rakettens antenne til bakken for å lage en live grafisk fremstilling av rakettens oppførsel under oppskyting og nedstigning.

## Mål for prosjektet
   - Datainnsamling: Samle relevante data under rakettens oppskyting.
   - Lagring og analyse: Lagring av dataene og videre analyse etter oppskyting.
   - Sanntidsvisualisering: Muliggjør visualisering av dataene i sanntid for å overvåke rakettens status.
   - Datavisualisering: Visualisere de innsamlede dataene etter oppskyting for å få innsikt i rakettens oppførsel.
