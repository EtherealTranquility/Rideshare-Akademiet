# Rideshare-Akademiet

## Prosjektbeskrivelse
Dette prosjektet handler om å samle og analysere data fra en rakett ved hjelp av en Arduino-enhet. Dataene skal enten lagres på et SD-kort eller sendes via rakettens antenne til bakken, for deretter å bli analysert og visualisert i Python. Den nøyaktige fremgangsmåten for payloaden er fortsatt usikker.

## Hva må gjøres/problemstillinger
1. **Arduino-programmering:**
   - Skriv Arduino-koden for å samle data fra sensorer under rakettens oppskyting.
   - Implementer koding for å lagre dataene på et SD-kort eller sende dem via rakettens antenne til bakken.

2. **Lagring av data:**
   - Alternativ 1: Lagre dataene på et **SD-kort**. Definer hvilket format dataene skal lagres i (f.eks. CSV, JSON).
   - Alternativ 2: Bruk rakettens **antenne** for å sende dataene til bakken i sanntid, og ta imot dataene med en mottaker.

3. **Format på lagrede data:**
   - Definer et passende format for lagring av dataene, for eksempel:
     - **CSV-format** for lett eksport til regneark.
     - **JSON-format** for lettere struktur og lesbarhet.

4. **Oppstart av kortet:**
   - Skriv en mekanisme for hvordan kortet skal starte, f.eks. automatisk ved tilkobling til strøm eller etter en bestemt tid (f.eks. et timer-trigger).

5. **Python-datavisualisering:**
   - Lag et Python-program som kan importere og visualisere de lagrede dataene fra SD-kortet eller antennemottakeren.
   - Visualiser dataene i form av grafer for å analysere rakettens oppskytning.

## Mål for prosjektet:
- Samle data under rakettens oppskyting.
- Lagring og analyse av data på bakken etter oppskyting.
- Visualisere data for å få innsikt i rakettens oppførsel under oppskytning og nedstigning.
